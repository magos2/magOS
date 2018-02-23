# Usage
#   cd /magOS/tools; bash ./gdb-qemu.sh kernel|userspace [b|break location]
# Youn can create an alias: alias kgdb='cd /magOS/tools; bash ./gdb-qemu.sh kernel'
set -x
ARCH=i386
CROSS_HOME=/opt/cross
if [ $1 == "kernel" ]; then
  CMD=/magOS/tools/gdb.cmd
elif [ $1 == "userspace" ]; then
  CMD=/magOS/tools/gdb-user.cmd
fi

if [[ ""$2 == "b" || ""$2 == "break" ]]; then
  EXC="-ex c"
  EXB="b $3"
fi

$CROSS_HOME/bin/$ARCH-elf-gdb -q -x $CMD -ex "$EXB" $EXC