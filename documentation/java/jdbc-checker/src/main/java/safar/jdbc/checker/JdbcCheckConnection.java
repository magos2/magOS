/* Author : @AR 2017   
 *   
 * Use this class to test connectivity to the database server    
 *   
 * /usr/lib/jvm/java-7-openjdk-amd64/bin/   
 * Compile: javac -cp ~/utils/postgresql-9.4.1212.jre6.jar JdbcCheckConnection.java   
 * Run: java -cp ~/utils/postgresql-9.4.1212.jre6.jar:.  safar/jdbc/checker/JdbcCheckConnection 1    
 */
package safar.jdbc.checker;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Properties;
import java.util.Random;

public class JdbcCheckConnection extends Thread {


	private Properties props;	
	int sqlCounter;   
	String driverType;
	static Thread threadConn;

	public JdbcCheckConnection(String driverType, int sqlCounter){
		this.driverType = driverType;
		this.sqlCounter = sqlCounter;
		props = new Properties();
		try {
			InputStream is = new FileInputStream(driverType + ".properties");
			props.load(is);
		} catch (IOException e) {
			System.out.println("I/O Error, cannot load file " + driverType + ".properties");
			e.printStackTrace();
			System.exit(1);
		}

	}

	public void run() {   
		String url = props.getProperty("url"); 
		String query = props.getProperty("query");
		//System.out.println("-- "  + "Connection to " + url);

		long start, duration, tmin = Long.MAX_VALUE, tmax = 0, tavg = 0, total = 0; //times in ms

		Connection conn = null;

		try {   
			start = System.currentTimeMillis();
			conn = DriverManager.getConnection(url, props);   
			duration = System.currentTimeMillis() - start;

			if (conn != null)   
				System.out.println("Connection Successful!: " + duration + " ms" );   

			for (int k = 1; k <= sqlCounter; k++) {  
				start = System.currentTimeMillis();
				PreparedStatement pst = conn.prepareStatement(query);   
				ResultSet rs = pst.executeQuery();   
				rs.close();   
				pst.close();   
				duration = System.currentTimeMillis() - start;
				total += duration; 
				if (tmin>duration) tmin = duration;
				if (tmax < duration) tmax = duration;
				Thread.sleep(new Random().nextInt(100)); //random sleep, 1 to 100 ms 
			}   
			tavg = total/sqlCounter;
			System.out.println("Executing " + sqlCounter + " SQL queries... "
					+ "min="+tmin+"ms ,max="+tmax+"ms, avg="+tavg+"ms");   
			conn.close();   
		} catch (Exception e) {   
			System.out.println("Connection Failed!");   
			e.printStackTrace();     
		} finally {    
			try {if (conn != null) conn.close();}   
			catch (Exception e) { e.printStackTrace();  }   
		}   
	}

	public static void main(String[] argv){   
		if (argv.length != 3) {
			System.out.println("Usage : JdbcCheckConnection oracle|mysql|postgresl connCounter sqlCounter");
			System.exit(1);
		}
		String driverType = argv[0];
		int connCounter = Integer.parseInt(argv[1]);  
		int sqlCounter = Integer.parseInt(argv[2]);
		for (int i = 1; i <= connCounter; i++) {   
			threadConn = new Thread(new JdbcCheckConnection(driverType, sqlCounter));   
			threadConn.start();   
		}   
	}
}
