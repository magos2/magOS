// Reverse enginnering tuto
// Compile
//   g++ -Wall file.cpp -o file.bin
// Disassable
//   objdump -d file.cpp
// Source : http://danielebellavista.blogspot.com/2014/10/reversing-c-binaries-2-objects.html
// ARMv7 assembler

class TestClass
{
  public:
  // _ZN9TestClassC1Ev
  // params : r0 = @this
  TestClass()
  {
    x = 5;          // add	r7, sp, #0
	y = 7;		  // str	r0, [r7, #4]   <-- r0 = @this, passed by param in r0
					// ldr	r3, [r7, #4]   <-- r3 = @this.x, offset=0
   		   	  // movs   r2, #5
  				  // str	r2, [r3, #0]   <-- this.x = 5
   				 // ldr	r3, [r7, #4]   <-- r3 = @this.y, offset = 4
   				 // movs   r2, #7
   				 // str	r2, [r3, #4]  <-- this.y = 7
    stuff = 9;
  }

  // _ZN9TestClassD1Ev
  // params : r0 = @this
  ~TestClass()
  {
    stuff = 0;
  }

  // _ZN9TestClass8GetStuffEv
  // params : r0 = @this
  // return : in r0
  int GetStuff()
  {
    return stuff; 	// push	{r7}
      				// sub	sp, #12
         			 // add	r7, sp, #0
        			  // str	r0, [r7, #4]
         			 // ldr	r3, [r7, #4]	; r3 = @this
        			  // ldr	r3, [r3, #8]    ; r3 = this.stuff, stuff-ofsset=8
       			   // mov	r0, r3		  ; resultat in r0
        			  // adds   r7, #12
         			 // mov	sp, r7
    				  // ldr.w  r7, [sp], #4
        			  // bx	 lr			  ; branch to link register(return address)

  }

  private:
  int x;
  int y;
  int stuff;
};


//-- Local Objects
//   The following function initialize a class onto the stack and calls the method GetStuff:
// _Z7OnStackv
int OnStack()
{
  TestClass t1;
  return t1.GetStuff();
  /*105ac:	b590         push	{r4, r7, lr}
   105ae:	b085      	sub	sp, #20
   105b0:	af00      	add	r7, sp, #0
   105b2:	1d3b      	adds   r3, r7, #4
   105b4:	4618      	mov	r0, r3  	;r0 = @t1 = sp+4
   105b6:	f000 f88d 	bl	 106d4 <_ZN9TestClassC1Ev>
   105ba:	1d3b      	adds   r3, r7, #4
   105bc:	4618      	mov	r0, r3      ; r0 = @t1
   105be:	f000 f8ab 	bl	 10718 <_ZN9TestClass8GetStuffEv>
   105c2:	4604      	mov	r4, r0
   105c4:	1d3b      	adds   r3, r7, #4
   105c6:	4618      	mov	r0, r3     ; r0 = @t1
   105c8:	f000 f898 	bl	 106fc <_ZN9TestClassD1Ev>
   105cc:	4623      	mov	r3, r4
   105ce:	4618      	mov	r0, r3
   105d0:	3714      	adds   r7, #20
   105d2:	46bd      	mov	sp, r7
   105d4:	bd90      	pop	{r4, r7, pc}   ; return by pop lr in pc!
   105d6:	bf00      	nop
  */
}


//-- Dynamic Allocated Object
//   An heap based initialization implies the use of the new and delete operator which respectively trigger 
//   the class constructor and destructor. The new operator, which resides in a shared library, performs a malloc, 
//   while the delete operator performs a free.
// _Z6OnHeapv
int OnHeap()
{
  // new: _Znwj@plt
  // con: _ZN9TestClassC1Ev
  TestClass* t1 = new TestClass(); // movs	r0, #12                   // size to pass to malloc
                                   // blx	104b4 <_Znwj@plt>          // new
                                   // mov	r4, r0  				   // object pointer returned in r0
                                   // mov	r0, r4
                                   // bl	 106d4 <_ZN9TestClassC1Ev>  // constructor

  int ret = t1->GetStuff();

  // des: _ZN9TestClassD1Ev
  // delete: _ZdlPv@plt
  delete t1;
  return ret;
}

//-- Global Objects
//   Both static and global objects are initialized before the main is called,
//   by an initialization routine. The same routine saves the new references and
//   the destructor address into a global table, where they will be destroyed by
//   the __run_exit_handlers routine, executed after the main function.
TestClass tg;
static TestClass ts;

int GlobalTc()
{
  return tg.GetStuff() + ts.GetStuff();
}

int main()
{
  OnStack();
  
  OnHeap();
  
  GlobalTc();
}
