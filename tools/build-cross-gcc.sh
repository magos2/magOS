#! /bin/bash
set -x
set -e
trap 'previous_command=$this_command; this_command=$BASH_COMMAND' DEBUG
trap 'echo FAILED COMMAND: $previous_command' EXIT

#-------------------------------------------------------------------------------------------
# This script will download packages for, configure, build and install a GCC cross-compiler.
# Customize the variables (INSTALL_PATH, TARGET, etc.) to your liking before running.
# If you get an error and need to resume the script from some point in the middle,
# just delete/comment the preceding lines before running it again.
#
# See: https://gcc.gnu.org/wiki/InstallingGCC
#      http://preshing.com/20141119/how-to-build-a-gcc-cross-compiler
#      http://wiki.osdev.org/GCC_Cross-Compiler
#      https://gcc.gnu.org/wiki/InstallingGCC
# NOTES: On Debian
#   - do "apt-get update" and "apt-get upgrade"
#   - Install packages : 
#          apt-get install build-essential g++ gcc make automake autoconf gawk wget libgmp-dev libmpc-dev libmpfr-dev 
#   - apt-get install linux-headers-$(uname -r)
#   - dont compile gmp, mpc and mpfr, instead install packages libgmp-dev libmpc-dev libmpfr-dev
#     
#-------------------------------------------------------------------------------------------
INSTALL_PATH=/opt/cross
SRC_PATH=/opt/sources
TARGET=i386-elf
#TARGET=arm-linux-gnueabihf
USE_NEWLIB=1
LINUX_ARCH=armhf
CONFIGURATION_OPTIONS="--with-sysroot --disable-nls --disable-werror" #--disable-multilib --disable-threads --disable-shared
PARALLEL_MAKE=-j4
BINUTILS_VERSION=binutils-2.24
GCC_VERSION=gcc-4.9.2
GDB_VERSION=gdb-7.11
WGET="wget --tries=120"
export PATH=$INSTALL_PATH/bin:$PATH

mkdir -p $INSTALL_PATH
mkdir -p $SRC_PATH

cd $SRC_PATH

# Download packages
download_gcc () {
  echo "Downloading gcc sources..."
  $WGET ftp://gd.tuwien.ac.at/gnu/gcc/releases/${GCC_VERSION}/${GCC_VERSION}.tar.gz
}

download_preq () {
  echo "### Downloading prerequisites #####"
  ./$GCC_VERSION/contrib/download_prerequisites
}

download_binutils () {
  echo "Downloading binutils sources..."
  $WGET https://ftp.gnu.org/gnu/binutils/${BINUTILS_VERSION}.tar.gz
}

download_gdb () {
  echo "### Downloading GDB #####"
  $WGET https://ftp.gnu.org/gnu/gdb/$GDB_VERSION.tar.gz
}


extract_gcc () {
  echo "### Extracting gcc... #####"
  for f in `ls -1d $GCC_VERSION.tar.gz`; do tar xf $f; done
}

extract_binutils () {
  echo "### Extracting binutils... #####"
  for f in `ls -1d $BINUTILS_VERSION.tar.gz`; do tar xfz $f; done
}

extract_gdb () {
  echo "### Extracting gdb... #####"
  for f in `ls -1d $GDB_VERSION.tar.gz`; do tar xfz $f; done
}
 
# Step 1. Binutils
build_binutils () {
  echo "### build-binutils #####"
  mkdir -p build-binutils
  cd build-binutils
  ../$BINUTILS_VERSION/configure -q --prefix=$INSTALL_PATH --target=$TARGET --with-sysroot --disable-nls --disable-werror
  make $PARALLEL_MAKE
  make install
  cd ..
}

# Step 3. C/C++ Compilers
build_gcc () {
  echo "### build-gcc #####"
  # The $PREFIX/bin dir _must_ be in the PATH. We did that above.
  which -- $TARGET-as || echo $TARGET-as is not in the PATH
  mkdir -p build-gcc
  cd build-gcc
  echo "configure gcc"
  ../$GCC_VERSION/configure -q --prefix=$INSTALL_PATH --target=$TARGET  --disable-nls --enable-languages=c --without-headers
  make $PARALLEL_MAKE all-gcc
  make $PARALLEL_MAKE all-target-libgcc
  make install-gcc
  make install-target-libgcc
  cd ..
}

build_gdb () {
  echo "### build-gdb #####"
  mkdir -p build-gdb
  cd build-gdb
  ../$GDB_VERSION/configure -q --prefix=$INSTALL_PATH --target=$TARGET  --disable-tui
  make $PARALLEL_MAKE
  make install
  cd ..
}

build_gdbserver () {
  echo "### build-gdbserver #####"
  mkdir -p build-gdbserver
  cd build-gdbserver
  ../$GDB_VERSION/gdb/gdbserver/configure -q --prefix=$INSTALL_PATH --host=$TARGET 
  make $PARALLEL_MAKE
  make install
  cd ..
}

## MAIN ###
# Step 1. download sourced
#download_gcc
#download_preq : dont use it, instead install packages gmp mpc mpfr
#download_binutils
#download_gdb

#extract_binutils
#extract_gcc
#extract_gdb

# Step 2. Binutils
build_binutils

# Step 3. Build gcc
build_gcc

# GDB install
build_gdb

#gdbserver optional
build_gdbserver

trap - EXIT
echo 'Success!'

