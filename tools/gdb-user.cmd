target remote localhost:1234
#for real mode debugging
#set architecture i8086
#set arch i386
symbol-file /magOS/bin/usr/user-debug.sym
#for real mode debugging
#break *0x7c00
#break *0x90200
#break  *0x1000
#break start_kernel
b *0x400000
c
