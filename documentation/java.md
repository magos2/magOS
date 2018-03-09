## HowTo
#### Disassembl the .class  
    javap -p -v Hello.class

#### exract one file from .jar  
    jar xvf rt.jar java/lang/Object.class  

#### extract one file from .zip  
    unzip -l myarchive.zip  
    unzip -j src.zip java/lang/Object.java
 
#### Construc a war
	mv myapp.war temp/
	cd temp/
	jar -xvf myapp.war
	rm myapp.war
	jar -cvf ../myapp.war *

#### Modify a file in a jar
    jar xf catalina.jar org/apache/catalina/util/ServerInfo.properties
    jar uf catalina.jar  org/apache/catalina/util/ServerInfo.properties    
	or
	zip -x|-u

#### Check if JAVA support 64 bits
	java -d64 -version
	
## JVM Tuning
see : http://blog.sokolenko.me/2014/11/javavm-options-production.html

#### Java >= 8 settings in production
    -server
    -Xms<heap size>[g|m|k] -Xmx<heap size>[g|m|k]
    -XX:MaxMetaspaceSize=<metaspace size>[g|m|k]
    -Xmn<young size>[g|m|k]
    -XX:SurvivorRatio=<ratio>
    -XX:+UseConcMarkSweepGC -XX:+CMSParallelRemarkEnabled
    -XX:+UseCMSInitiatingOccupancyOnly -XX:CMSInitiatingOccupancyFraction=<percent>
    -XX:+ScavengeBeforeFullGC -XX:+CMSScavengeBeforeRemark
    -XX:+PrintGCDateStamps -verbose:gc -XX:+PrintGCDetails -Xloggc:"<path to log>"
    -XX:+UseGCLogFileRotation -XX:NumberOfGCLogFiles=10 -XX:GCLogFileSize=100M
    -Dsun.net.inetaddr.ttl=<TTL in seconds>
    -XX:+HeapDumpOnOutOfMemoryError -XX:HeapDumpPath=<path to dump>`date`.hprof
    -Djava.rmi.server.hostname=<external IP>
    -Dcom.sun.management.jmxremote.port=<port> 
    -Dcom.sun.management.jmxremote.authenticate=false 
    -Dcom.sun.management.jmxremote.ssl=false

#### Large Heap Memory  
Java 64 has no limit of heap memory (>100Go). But GC pauses increase a lot(stop-the-world). Pauses of several tens of seconds 
if Xmx<30Go, and several minutes if >30Go. Tunning: use __-XX:+UseConcMarkSweepGC__. If Xmx<4Go there is no problem.

#### Preserve Memory
Disable loading JVMs Graphic Library: Option  "-Djava.awt.headless=true"

  
## Out Of Memory
**Generate a heapdump**

    jmap -histo -F 6764
    jmap -F -d64 -dump:format=b,file=tempheap.bin 6764
	

**Eclipse Memory Analyzer (MAT)**: very good tool for analysing of HeapDump


## Thread Dump : High CPU

Tools: 
	
	jstack (jstack  -J-d64  -m 24326 >> appli1.tdump)
	
	JVisualVM

1. Genrerer des threads dumps : kill -3 pid, ou

1.1 jstack  -J-d64  -m 24326 >> appli1.tdump

2. Lancer la commande **top**, puis entrer **H** pour show threads on.

3. Identifier le thread qui a le plus de CPU et TIME+

```
  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+     COMMAND
10477 tomcat    20   0 13.2g 6.2g  15m R 300  19.9    501:08.65 java
10456 tomcat    20   0 13.2g 6.2g  15m R 47.6 19.9    523:25.89 java
10447 tomcat    20   0 13.2g 6.2g  15m R 47.2 19.9    513:57.74 java
24363 tomcat    20   0 13.2g 6.2g  15m R 46.3 19.9    520:55.67 java
```

4. le thread le plus consommatrice est **10477**, transformé en hex, **0x28ed**. Le thread coupable est trouvé dans threadDump **nid=0x28ed**

```
"asyncThread-16" daemon prio=10 tid=0x00007f81f0035800 nid=0x28ed runnable [0x00007f81d209e000]
   java.lang.Thread.State: RUNNABLE
	at java.util.HashMap.put(Unknown Source)
```

[Analysis cpu high](https://blogs.oracle.com/jiechen/analysis-against-jvm-thread-dump-cpu-high-usage-issue)

## Thread Dump: Dead Lock
[Analysis cpu high](https://blogs.oracle.com/jiechen/analysis-against-jvm-thread-dump-dead-lock)

## Thread Dump: Resource Contention
[Analysis Resource Contention](https://blogs.oracle.com/jiechen/analysis-against-jvm-thread-dump-resource-contention)

## Thread Dump: Out Of Thread
[Analysis Out Of Thread](https://blogs.oracle.com/jiechen/analysis-against-jvm-thread-dump-out-of-thread)


## Java Tools
#### JavaMelody
https://github.com/javamelody/javamelody

#### MAT : Eclipse Memory Analyzer



## JVM Implementation 
- Data Types :
  * Primitive types : returnAncress, byte, short, int, long,char, float, double, boolean.
  * Refefence type : class type, interface type, and array type.
- Word Size :
  The basic unit of size for data values in the JVM is the word--a fixed size. 
  The word size must be large enough to hold a value of type byte, short, int, char, float, 
  returnAddress, or reference. 
  Two words to hold long or double. 
  The word size is often chosen to be the size of a native pointer on the host platform.
  
- Constant Pool
  per class. several types of data is stored in the constant pool including numeric, string literals, 
  class/field/method references.
  for example, the code
```java
    Hello hello = new Hello();
  will be translated in bytecode:
    new #9    // class Hello
    dup
    invokespecial #10   // Method "<init>":()V
  constantPool :
    #9 = Class         #41        // Hello
    #10 = Methodref    #9.#32     // Hello."<init>":()V
```

- Frame
  A new frame is created and pushed to the top of stack for every method invocation. 
  The frame is removed (popped) when the method returns normally or if an uncaught exception. .

  Each frame contains:
   * Local variable array
   * Return value
   * Operand stack
   * Reference to runtime constant pool for class of the current method
  
- Local Variables Array
  The array of local variables contains a reference to this, all method parameters and  locally defined variables. 
  For class methods (i.e. static methods) the method parameters start from zero, however, 
  for instance method the zero slot is reserved for this.
  
- Operand Stack
  The operand stack is used during the execution of byte code instructions in a similar way that 
  general-purpose registers are used in a native CPU.  
  Example
```
    int i, j=4;
    i = j + 5;
  Bytecode
    iconst_4  //push 4 on operand stack
    istore_2  //pop 4, updtate locals var 2(j), j=4
    iload_2   //load local var 2 (j), from the local array, push it 
    iconst_5  // push 5 on operand stack
    iadd      //pop 5 and j,  do add(j+5), push the result 
    istore_1  //pop the result, update the local var 1 (i) in the local array.
``` 

- Class Loaders
  * Bootstrap Classloader: top classloaders. is usually implemented as native. The bootstrap classloader is responsible for loading the basic Java APIs(rt.jar). 
  * Extension Classloader: loads classes from standard Java extension APIs such as security extension functions.
  * System Classloader: is the default application classloader, which loads application classes from the classpath.
  * User Defined Classloaders:  can alternatively be used to load application classes.(cf. tomcat)
  
- Classloader Reference
  All classes that are loaded contain a reference to the classloader that loaded them. 
  In turn the classloader also contains a reference to all classes that it has loaded.
  
## Bytecode
- disassemler un .class
```sh
  javap -v -p -s -sysinfo -constants Hello.class
```

- la JVM est une machine a pile. elle ne fait pas d'hypothese 
  sur le nombre de registres.
- dans une machine à pile
  * Les opérandes à manipuler sont placées sur une pile
  * Une instruction
    - dépile zéro, un ou plusieurs opérandes ;
	 - réalise son opération ;
	 - puis empile son résultat
  * En bytecode Java, opérande = mot de 32 bits
	  les opérandes long et double requièrent 2 cases de pile

- soit l'instruction
```java
  i = j + k;
  _le code generé pour une machine a pile(L pour load, S pour store)
  load j  #L S
  load k  #L S
  add     #L L S, pop j and k, do add, and push the result on top of stack
  store i #L S, depile  le resultat de la pile, et la mettre dans i(variable locale)
```
  
- JIT(just in time compiler): consiste a traduire le byte code en language machine au fur et a mesure
  de son decodage. gain de 10  a 100 par rapport au bytecode interpreté
  
- Decompiler
```
  java -p HelloWorld
```
  
- exemple de bytecode
```
int i;
for ( i=0 ; i<10 ; i++) ;
 0 iconst_0 # mettre 0 sur la pile
 1 istore_1 # vider la pile dans la première variable
 2 goto 8
 5 iinc 1 1 # ajouter 1 à la première variable
            # (on ne peut pas incrémenter
            # directement sur la pile)
 8 iload_1   # empiler la premiere variable
 9 bipush 10 # mettre 10 sur la pile
 11 if_icmplt 5 # comparer les deux valeurs en sommet de pile
 •••
 36 return
```
  
- The core of a VM consists of a fetch-decode-execute loop:
```
pc = code.start;
while(true)
{ 
	npc = pc + instruction_length(code[pc]);
	switch (opcode(code[pc]))
	{ 
	case ILOAD_1: push(locals[1]);
				  break;
	case ILOAD: push(locals[code[pc+1]]);
				break;
	case ISTORE: t = pop();
				 locals[code[pc+1]] = t;
				 break;
	case IADD: t1 = pop(); t2 = pop();
			   push(t1 + t2);
			   break;
	case IFEQ: t = pop();
				if (t==0) npc = code[pc+1];
				break;
	...
	}
	pc = npc;
}
```
  
* Descripteurs de type
  - Descripteurs pour les types primitifs  
	 boolean:Z, byte:B, char:C, short:S, int:I, long:J , float:F, double:D
  - Descripteurs pour les classes :
	 Classe : Lpackage/subpackage/.../MyClass ;  
	 Tableau : préfixe '[' (exemple : double[][] : [[D)
  - Descripteurs pour les méthodes : 
	 (typearg1typearg2...)typeretour  
	 ➔ Exemple : long[] f(int i, Class[] classes)
                (I[Ljava/lang/Class;)[J
  
* Instructions de bytecode Java
```
	Une instruction = 1 octet. 256 instruction possibles
    iconst_0 : charge l'entier 0 sur la pile
    iload_0 : on empile la variable locale 0
	iload_1 : on empile la variable locale 1
	iadd : on dépile 2 éléments et on empile leur somme
	i2f : on dépile 1 élément int et on empile sa conversion en float
	fconst_2 : on empile la constante 2.0f
	fdiv : on divise deux éléments dépilés et on empile le résultat
  - {i,l,f,d,a,b,c,s}aload [arrayref, index] : chargement sur la pile 
    d'un primitif ou référence
  - {i,l,f,d,a,b,c,s}astore [arrayref, index, value] : mise à jour d'une 
    cellule d'un tableau
  - invocation de methodes
	 invoke{static, special, virtual, interface, dynamic} <@class/method> 
    [ref, arg1, arg2, …]
```
  
- Récapitulatif d'instructions 
essentielles... pour IR2012
  * Chargement de constantes int et String : ldc
  * Chargement et sauvegarde de variables locales int (entier 
    et booléen) et référence (vers String) : {i,a}load, {i,a}store
  * Les fonctions sont des méthodes statiques privées d'une 
    classe appelées par invokestatic
  * Il faudra récupérer System.out (getstatic) et appeler println 
    (invokevirtual)
  * Opérations sur les int : iadd, isub, imul, idiv, ineg
  * Saut conditionnel pour booléen faux (entier 0) : ifeq
  * Retour d'un entier (ireturn) ou d'une référence string(areturn)
  
-- new 
  the new opcode is only used to “create a reference” of the type, but in order to initialize the object it is still required to call <init> on that object reference. 
  In fact, the four-instruction-sequence (new/dup/invokespecial <init()>/astore) is a common pattern, when an object is 
  new’ed and stored into a local variable. 
  
## Fetch-Decode-Execute process
Code de:
```
   public static void main(String[] zArgs){
		Hello hello = new Hello();
		hello.sayHello("Anass");
	}
```
- Used Registers : PC - Programm Counter, IR - Instruction Register
- Fetch : load into IR the instruction pointed by PC, and increment it,
- Decode : decode the instruction, fetch operands
- Execute the instruction 
```
 pc
  -----
 |  9  |
  -----
    |              Memory
    |            ---------------------
    |          0 |  new #11          |                 Stack
    |            ---------------------             -------------- 
    |          3 |  dup              |             | "Anass"    |
    |            ---------------------             --------------
    |          4 | invokespecial #12 |             |            | 
    |            ---------------------             --------------
    |          7 |  astore_1         |             |            |   
    |            ---------------------             --------------
    |          8 |  alode_1          |
    |            ---------------------________________
    |--------> 9 |  ldc #13          |-------         | Fetch
                 ---------------------       |        V 
                 | invokevirtual #14 |       |     ---------------  
                 ---------------------       |     | ldc #13     |
                 |  return           |       |     ---------------
                 ---------------------       |       IR (Instruction Register)
                                             |
                                             |
                  Constant Pool              |
                  ---------------            |
             #11 |  Hello Class  |           |
                  ---------------            |
             #12 |   init()      |           |
                  ---------------            |
             #13 |   "Anass"     | <---------|
                  ---------------
             #14 |   sayHello()  |
                  ---------------
               
```

  

## Bytecode samples
```
 -------------------------------------------
 |   //calculate 2^n		0x4  iconst_1  |
 |   int pow2(int n) {	  0x1b iload_1   |
 |     return (1<<n);	   0x78 ishl      |
 |   }	      			0xac ireturn   |
 -------------------------------------------
```		          
		  
## Docs 
- JVM Specs
  https://docs.oracle.com/javase/specs/index.html
- JVM internals :http://blog.jamesdbloom.com/JVMInternals.html
- https://www.artima.com/insidejvm/ed2/jvmP.html
- BCEL : The Byte Code Engineering Library 
  https://commons.apache.org/proper/commons-bcel/
- java class file format
	https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html
- http://blog.jamesdbloom.com/JVMInternals.html
- http://zeroturnaround.com/rebellabs/java-bytecode-fundamentals-using-objects-and-calling-methods/

  
  
  
  
  
  
  
  
  
  
  
  
