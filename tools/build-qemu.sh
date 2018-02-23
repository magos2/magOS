#! /bin/bash
set -x
set -e
trap 'previous_command=$this_command; this_command=$BASH_COMMAND' DEBUG
trap 'echo FAILED COMMAND: $previous_command' EXIT

#-------------------------------------------------------------------------------------------
# This script will download packages for, configure, build and install a QEMU.
# NOTES: On Debian
#   - Install packages : apt-get install  g++ make  libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev ncurses-dev
#     
#-------------------------------------------------------------------------------------------
INSTALL_PATH=/opt/qemu
SRC_PATH=/opt/sources
QEMU_VERSION=qemu-2.6.2
TARGET=i386-softmmu
PARALLEL_MAKE=-j4
export PATH=$INSTALL_PATH/bin:$PATH

mkdir -p $INSTALL_PATH
mkdir -p $SRC_PATH

cd $SRC_PATH

# Download packages
download_qemu () {
  echo "Downloading qemu sources from http://wiki.qemu.org/Download"
  exit 1
}

extract_qemu () {
  tar xvfJ $QEMU_VERSION.tar.xz	
}

build_qemu () {
  echo "### build-qemu #####"
  mkdir -p build-qemu
  cd build-qemu
  ../$QEMU_VERSION/configure --enable-debug --disable-kvm --enable-curses --prefix=$INSTALL_PATH --target-list=$TARGET --disable-vnc
  make $PARALLEL_MAKE
  make install
  cd ..
}


## MAIN ##
#download_qemu
extract_qemu
build_qemu

trap - EXIT
echo 'Success!'

