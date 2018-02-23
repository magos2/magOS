target remote localhost:1234
#for real mode debugging
#set architecture i8086
#set arch i386
symbol-file /magOS/bin/kernel/kernel-debug.sym
#symbol-file /magOS/bin/usr/user-debug.sym
#for real mode debugging
#break *0x7c00
#break *0x90200

#this break in _start
#this is the entry address and a load address: objdump -f kernel.elf
#
#break  *0x10000c
#c
#
#break _start
#break startup_32
break start_kernel
c
