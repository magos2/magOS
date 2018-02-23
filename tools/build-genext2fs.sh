#! /bin/bash
# this build genext2fs from sources
# download from: https://sourceforge.net/projects/genext2fs/files/genext2fs/1.4.1/
#     
#     
set +x
set -e
trap 'previous_command=$this_command; this_command=$BASH_COMMAND' DEBUG
trap 'echo FAILED COMMAND: $previous_command' EXIT

export PATH=$PATH:/opt/cross/bin

GENEXT2FS_VERSION=genext2fs-1.4.1
INSTALL_PATH=/opt/genext2fs
SRC_DIR=/opt/sources

## prereq
#apt install autoconf -y

mkdir -p $SRC_DIR
cd $SRC_DIR

extract () {
  if [ ! -f $GENEXT2FS_VERSION.tar.gz ]; then
    echo ERROR: download source file $GENEXT2FS_VERSION.tar.gz into path $SRC_DIR
    exit 1
  fi
  tar xvfz $GENEXT2FS_VERSION.tar.gz
}

build () {
  cd $GENEXT2FS_VERSION
  ./configure -q --prefix=$INSTALL_PATH 
  make
  make install
}
extract
build
echo install success
