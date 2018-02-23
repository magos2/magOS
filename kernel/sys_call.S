/*
 * INT :  does automatiquely
     -  without previlege transition
        ss:esp = old ss:esp
        push  eflags
        pushd cs
        push  eip
        push errorCode #if any
        
     - with previlege transition
        ss:esp = from TSS
        pushd old_ss
        push  old_esp
        push  eflags
        pushd cs
        push  eip
        push errorCode #if any
 * IRET :  does automatiquely certain pops then does return
     - return to same previlege level
       pop eip
       pop cs
       pop eflags
       
     - return to outer previlege level
       pop eip
       pop cs
       pop eflags
       pop esp
       pop ss
 
* System Call:
  %eax  sys call number
  %ebx  arg1
  %ecx  arg2
  %edx  arg3
  %esi  arg4
  %edi  arg5
 */

.att_syntax noprefix

#include <segment.h>


FIRST=1
SECOND=2

/*if you modify this, you must do the same in ptrace.h*/ 
_EBX  = 0
_ECX  = 4
_EDX  = 8
_ESI  = 12
_EDI  = 16
_EBP  = 20
_EAX  = 24
_ES   = 28
_DS   = 32
_ERROR_CODE = 36
_EIP  = 40
_CS   = 44
_EFLAGS  = 48
_ESP = 52
_SS  = 56


.global irq_0, irq_1, irq_14, irq_15
.global system_call, ret_from_syscall, isr_default
.global divide_error,_debug,int3,overflow,reserved,double_fault,triple_fault
.global invalide_tss, segment_not_present, stack_segment_fault, gpf, page_fault
.global do_switch, ret_from_switch, ret_from_fork

.extern sys_call_table, timer_handler, keyboard_handler, ide_handler

# EOI : End Of Interrput acknowlegment. If not PIC wont handle anymore
.macro ack_pic chip
  push eax
  push edx
  mov $0x20, al
.if \chip==1
  mov $0x20, dx
.elseif \chip==2
  mov $0xA0, dx
.endif
  outb al, dx
  jmp 1f
1:pop edx
  pop eax
.endm

.macro SAVE_ALL
   pushl ds
   pushl es
   push eax
   push ebp
   push edi
   push esi
   push edx
   push ecx
   push ebx   /*pushs in this order, system call args*/
   mov $KERNEL_DS, eax
   mov ax, ds
   mov ax, es
   mov $USER_DS, eax
   mov ax, fs
   mov ax, gs
   mov _EAX(esp), eax  #restore eax
   xor ebp, ebp /*zero first ebp, useful to show_trace*/
.endm

.macro RESTORE_ALL    
   pop ebx
   pop ecx
   pop edx
   pop esi
   pop edi
   pop ebp
   pop eax
   popl es   
   popl ds
   add $4, esp  #code error
.endm

  
system_call:
   pushl $0  #code error
   SAVE_ALL
   mov $sys_call_table, ebx  
   mov (ebx, eax, 4), edx    /*eax=system call nr, args are pushed on the stack*/
   mov esp, eax              /*pt_regs*/
   push eax
   call *edx 
   add $4, esp
   mov eax, _EAX(esp)  /*passing return value to the caller*/
   RESTORE_ALL
   iret
 
ret_from_switch:
  add $4, esp #pop eip done by 'call ret_from_switch"
  pop esi
  pop edi
  pop ebx
  pop ebp
  ret      

ret_from_fork:
  add $4, esp
  RESTORE_ALL
  iret
   
irq_0: /*Timer*/
   pushl $0  #code error
   SAVE_ALL
   ack_pic 1
   mov esp, eax
   push eax
   call timer_handler
   add $4, esp
   orl $0x200, _EFLAGS(esp)   #enable interrupt just after iret
   RESTORE_ALL
   iret

irq_1: /*Keyboard*/
   pushl $0  #code error
   SAVE_ALL
   ack_pic 1
   call keyboard_handler
   orl $0x200, _EFLAGS(esp)   #enable interrupt just after iret
   RESTORE_ALL
   iret

ATA_PRIMARY_CTRL   = 0
ATA_SECONDARY_CTRL = 1

irq_14: /*IDE primary controller*/
   pushl $0  #code error
   SAVE_ALL
   ack_pic 1
   pushl $ATA_PRIMARY_CTRL
   call ide_handler
   orl $0x200, _EFLAGS(esp)   #enable interrupt just after iret
   RESTORE_ALL
   iret
irq_15: /*IDE secondary controller*/
  hlt

.macro DO_EXCEPTION isr_name errcode=witherr_code
\isr_name:
   cli
.if \errcode==noerr_code
   pushl $0  #code error not used
.endif
   SAVE_ALL
   mov _ERROR_CODE(esp), eax  #error code
   mov esp, ebx               #esp
   push eax  
   push ebx  
   call do_\isr_name
   add $8, esp
   orl $0x200, _EFLAGS(esp)   #enable interrupt just after iret
   RESTORE_ALL
   iret
.endm
   
DO_EXCEPTION divide_error noerr_code
DO_EXCEPTION _debug       noerr_code
DO_EXCEPTION int3         noerr_code
DO_EXCEPTION overflow     noerr_code
DO_EXCEPTION double_fault
DO_EXCEPTION triple_fault
DO_EXCEPTION invalide_tss
DO_EXCEPTION segment_not_present
DO_EXCEPTION stack_segment_fault
DO_EXCEPTION gpf
DO_EXCEPTION page_fault
DO_EXCEPTION reserved     noerr_code

isr_default:
  iret

.end