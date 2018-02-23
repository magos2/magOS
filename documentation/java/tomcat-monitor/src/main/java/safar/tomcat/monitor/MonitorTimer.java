package safar.tomcat.monitor;

import java.util.Timer;
import java.util.TimerTask;

public class MonitorTimer extends TimerTask {

	Timer timer;
	TomcatMonitor tomcatMonitor;
	
	public void start () {
		try {
			tomcatMonitor = TomcatMonitor.getInstance();
			tomcatMonitor.openFiles();
			int period = tomcatMonitor.getPeriod(); //seconds
			int delay  = 3;
			timer = new Timer();
			timer.schedule(this, delay*1000, period*1000);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		try {
			tomcatMonitor.logAttributes();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void stop() {
		timer.cancel();
	}

}
