package safar.tomcat.monitor;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

@WebListener
public class MonitorListener implements ServletContextListener {
	
	MonitorTimer timer;
	
	@Override
	public void contextInitialized(final ServletContextEvent servletContextEvent) {
		timer = new MonitorTimer();
		timer.start();
	}

	@Override
	public void contextDestroyed(ServletContextEvent arg0) {
		timer.stop();
	}

}
