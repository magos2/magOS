#! /bin/bash
# this build grub2 from sources
# see http://pete.akeo.ie/2014/05/compiling-and-installing-grub2-for.html?m=1
#     http://wiki.osdev.org/GRUB
# Pre-requisities:
#	apt-get install bison flex autoconf xorriso 
#	
set -x
set -e
trap 'previous_command=$this_command; this_command=$BASH_COMMAND' DEBUG
trap 'echo FAILED COMMAND: $previous_command' EXIT

export PATH=$PATH:/opt/cross/bin:/opt/qemu/bin

INSTALL_PATH=/opt/grub
SRC_DIR=/opt/sources
GRUB_VERSION=latest
PARALELL=-j1
TARGET=i386-elf
TARGET_CC='TARGET_CC=i386-elf-gcc TARGET_OBJCOPY=i386-elf-objcopy TARGET_STRIP=i386-elf-strip TARGET_NM=i386-elf-nm TARGET_RANLIB=i386-elf-ranlib'

install_prereq () {
  apt-get install bison flex autoconf xorriso -y
}

mkdir -p $SRC_DIR
cd $SRC_DIR

download_grub() {
  echo "download grub sources from http://ftp.gnu.org/gnu/grub/"
  git clone --depth 1 http://git.savannah.gnu.org/grub.git grub-$GRUB_VERSION
}

extract_grub () {
  tar xvfz grub-$GRUB_VERSION.tar.gz
}

build_grub () {
  cd grub-$GRUB_VERSION
  #autogen if sources got from GIT
  ./autogen.sh
  ./configure  --prefix=$INSTALL_PATH --target=$TARGET $TARGET_CC --disable-nls  --disable-efiemu
  make $PARALELL
  make install
}

#install_prereq
#download_grub
#no extract if download from git
#extract_grub
build_grub

trap - EXIT
echo 'Success!'
