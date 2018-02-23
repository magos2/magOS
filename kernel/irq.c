/* Copyrigth 2016 @AR
 * 
 * irq.c definit le handler de traitement des interruptions matirielles non masques. 
 * puis initialise le IDT sur les entrées de 32 a 47, supposant qu'on dispose de deux controlleur PIC 8259A, 
 * maitre et esclave.
 * IRQ 0: Timer
 * IRQ 1: Keyboard
 * IRQ 2:
*/ 
#include <irq.h>
#include <idt.h>
#include <io.h>
#include <kernel.h>
#include <keyboard.h>
#include <sched.h>

#define IRQ_0  32  /*Timer*/
#define IRQ_1  33  /*keyboard*/
#define IRQ_2  34
#define IRQ_3  35
#define IRQ_4  36
#define IRQ_5  37
#define IRQ_6  38
#define IRQ_7  39
#define IRQ_8  40  /*system clock*/
#define IRQ_9  41 
#define IRQ_10 42
#define IRQ_11 43  /*network interface*/
#define IRQ_12 44  /*PS/2 mouse*/
#define IRQ_13 45  /*mathematical coprocessor*/
#define IRQ_14 46  /*hd primary controler*/
#define IRQ_15 47  /*hd secondary controler*/

void irq_0(void);
void irq_1(void);
void irq_14(void);
void irq_15(void);

void do_irq_2()
{
}
void do_irq_3()
{
}
void do_irq_4()
{
}
void do_irq_5()
{
}
void do_irq_6()
{
}
void do_irq_7()
{
}
void do_irq_8()
{
}
void do_irq_9()
{
}
void do_irq_10()
{
}
void do_irq_11()
{
}
void do_irq_12()
{
}
void do_irq_13()
{
}


/* init the PIC 8259A (Programmabl3 Interrupt Controller) 
 */
void _8259a_init()
{
   /* Init de ICW1,ICW2,ICW3 et ICW4 du Maitre(Port 0x20/0x21), Slave 0xA0/0xA1*/
   outb_p(0x11, 0x20);  
   outb_p(0x11, 0xA0); 
   outb_p(0x20, 0x21); //maître, vecteur de départ = 32
   outb_p(0x70, 0xA1); //esclave, vecteur de départ = 96
   outb_p(0x04, 0x21); 
   outb_p(0x02, 0xA1); 
   outb_p(0x01, 0x21); 
   outb_p(0x01, 0xA1); 
   
   /* Init de OCW1 à 4 */

}

void irq_init()
{
   _8259a_init();
   
   set_intr_gate(IRQ_0, (u32) irq_0);
   set_intr_gate(IRQ_1, (u32) irq_1);   
   set_intr_gate(IRQ_14, (u32) irq_14);   
   set_intr_gate(IRQ_15, (u32) irq_15);   
}








