#!/bin/sh
# Usage :
#        ./start-qemu.sh [-g]
# Options qemu
#   -monitor stdio
#   logs : -D /var/log/qemu.log -d cpu_reset,mmu,guest_errors
#       
#Boot order
#  -boot c - Boot the first virtual hard drive.
#  -boot d - Boot the first virtual CD-ROM drive.
#  -boot n - Boot from virtual network.
#
set +x

KERN_IMG=/usr/local/images/disk.img
KERN_ISO=/usr/local/images/magos.iso
ARCH=i386
QEMU_HOME=/opt/qemu
QEMU_OPTS='-vga std -curses -show-cursor -full-screen -no-fd-bootchk -D $LOGFILE'
LOGFILE=/tmp/qemu.log
LOGOPT="-d cpu_reset,mmu,guest_errors"
export PATH=$PATH:$QEMU_HOME/bin

if [ ""$1 == "-g" ] ; then
  DEBUG="-s  -S"
fi
$QEMU_HOME/bin/qemu-system-$ARCH -m 32  $DEBUG  $QEMU_OPTS -boot d  -cdrom $KERN_ISO -hda $KERN_IMG -D $LOGFILE $LOGOPT


