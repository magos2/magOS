###### Notes ######
- Disassemble 
  javap -c Hello.class
  javap -v Hello.class : show constant pool

* On Termux:
  $ apt update & apt upgrade
  $ packages install clang gdb
  $ apt install make
  $ termux-setup-storage
    allow access on storage; see https://termux.com/storage.html
  $ cd $HOME
  $ ln -s /sdcard/Android/data/com.ma.../files.../magOS
  $ make init
  $ gdb --args $HOME/usr/local/bin/janin $HOME/magOS/jvm-c/test/Hello.class
* Environment:
  termux


#### Example: Class Hello.java ####
javap -v Hello.class
/**
Constant pool:
   #1 = Methodref          #6.#19         // java/lang/Object."<init>":()V
   #2 = Fieldref           #3.#20         // Hello.stock:I
   #3 = Class              #21            // Hello
   #4 = Methodref          #3.#19         // Hello."<init>":()V
   #5 = Methodref          #3.#22         // Hello.growStock:(I)I
   #6 = Class              #23            // java/lang/Object
   #7 = Utf8               stock
   #8 = Utf8               I
   #9 = Utf8               <init>
  #10 = Utf8               ()V
  #11 = Utf8               Code
  #12 = Utf8               LineNumberTable
  #13 = Utf8               growStock
  #14 = Utf8               (I)I
  #15 = Utf8               main
  #16 = Utf8               ([Ljava/lang/String;)V
  #17 = Utf8               SourceFile
  #18 = Utf8               Hello.java
  #19 = NameAndType        #9:#10         // "<init>":()V
  #20 = NameAndType        #7:#8          // stock:I
  #21 = Utf8               Hello
  #22 = NameAndType        #13:#14        // growStock:(I)I
  #23 = Utf8               java/lang/Object
**/
public class Hello{
	int stock;
	
   /**Code:
      stack=3, locals=2, args_size=2
         0: aload_0
         1: dup
         2: getfield      #2                  // Field stock:I
         5: iload_1
         6: iadd
         7: putfield      #2                  // Field stock:I
        10: aload_0
        11: getfield      #2                  // Field stock:I
   **/
	int growStock(int n) {
	 stock += n;
    return stock;
	}
	
   /**Code:
      stack=2, locals=3, args_size=1
         0: new           #3                  // class Hello
         3: dup
         4: invokespecial #4                  // Method "<init>":()V
         7: astore_2
         8: aload_2
         9: bipush        8
        11: putfield      #2                  // Field stock:I
        14: aload_2
        15: bipush        7
        17: invokevirtual #5                  // Method growStock:(I)I
        20: istore_1
        21: return
   **/
	public static void main(String[] zArgs){
		int k;
		Hello hello = new Hello();
		hello.stock = 8;
		k = hello.growStock(7);
   }
}
