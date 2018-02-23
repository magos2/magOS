
public class Hello{
	String name;
	int year;
	
	//calculate 2^n
	int pow2(int n) {
	 return (1<<n);
	}
	
	void sayHello(String name) {
	    System.out.println("Hello " + name);
	}
	
	public static void main(String[] zArgs){
		int k;
		Hello hello = new Hello();
		hello.year = 2013;
		k = hello.pow2(7);
		hello.sayHello("Anass");
	}
}
