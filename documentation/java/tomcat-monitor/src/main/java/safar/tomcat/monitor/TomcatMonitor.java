/**
 * CR @AR 2017
 * 
 * This the main  to monitor the Tomcat Mbeans. 
 * I insipred it from  Tomcat JMX Proxy Servlet.
 * 
 * Request format:
 *    http://webserver/manager/jmxproxy/?get=BEANNAME&att=MYATTRIBUTE&key=MYKEY
 *    
 *    http://webserver/tomcat-monitor-0.0.1-SNAPSHOT/monitor/?mbean=BEANNAME&att=MYATTRIBUTE&key=MYKEY
 *    
 * Examples: 
 *    http://localhost:8080/tomcat-monitor-0.0.1-SNAPSHOT/monitor?get=Catalina:*
 *    http://localhost:8080/tomcat-monitor/monitor?get=java.lang:type=Memory&att=HeapMemoryUsage
 *    http://localhost:8080/tomcat-monitor-0.0.1-SNAPSHOT/monitor?get=java.lang:type=Memory&att=HeapMemoryUsage&key=max
 *    http://localhost:8080/tomcat-monitor/monitor?get=*=*
 * 
 * Object Name Syntax
 *    domain: key-property-list
 *    For example:
 *      com.sun.someapp:type=Whatsit,name=25    
 *      
 * Docs:
 *    http://www.oracle.com/technetwork/articles/java/best-practices-jsp-136021.html
 *    http://svn.apache.org/repos/asf/tomcat/trunk/java/org/apache/catalina/manager/JMXProxyServlet.java
 */

package safar.tomcat.monitor;

import java.io.InputStream;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Set;

import javax.management.MBeanServer;
import javax.management.ObjectName;
import javax.management.openmbean.CompositeData;
import javax.servlet.ServletException;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.apache.catalina.mbeans.MBeanDumper;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.tomcat.util.modeler.Registry;

import safar.tomcat.monitor.MonitoredMBean.Attribute;

@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class TomcatMonitor {

	@XmlTransient
	private static TomcatMonitor tomcatMonitor;

	@XmlTransient
	MBeanServer mBeanServer;

	@XmlTransient
	Registry registry;

	@XmlAttribute
	int period;

	@XmlElement(name="monitoredMBean")
	MonitoredMBean[] monitoredMBeans;

	static final Logger logger = LogManager.getLogger(TomcatMonitor.class);

	public void init() throws Exception {
		registry = Registry.getRegistry(null, null);
		mBeanServer = registry.getMBeanServer();
	}

	public static TomcatMonitor getInstance() throws Exception{
		if (null == tomcatMonitor) {
			ClassLoader classLoader = Thread.currentThread().getContextClassLoader();
			InputStream xml = classLoader.getResourceAsStream("monitored-mbeans.xml");

			JAXBContext jc = JAXBContext.newInstance(TomcatMonitor.class);
			Unmarshaller unmarshaller = jc.createUnmarshaller();
			tomcatMonitor = (TomcatMonitor) unmarshaller.unmarshal(xml);

			Marshaller marshaller = jc.createMarshaller();
			marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
			marshaller.marshal(tomcatMonitor, System.out);

			tomcatMonitor.init();
		}
		return tomcatMonitor;
	}


	public void openFiles() {
		for (MonitoredMBean monitoredMBean : monitoredMBeans)
			monitoredMBean.writeHead();
	}


	public void logAttributes() throws Exception {
		ArrayList<String> values;
		for (MonitoredMBean monitoredMBean : monitoredMBeans) {
			values = new ArrayList<>();
			for (Attribute attribute: monitoredMBean.attributes) {
				if (null != attribute.keys)
					for (String key : attribute.keys) { 
						String value = getAttribute (monitoredMBean.name, attribute.name, key);
						values.add(value);
					}
				else {
					String value = getAttribute (monitoredMBean.name, attribute.name, null);
					values.add(value);
				}
			}
			monitoredMBean.writeValues(values);
		}
	}

	String getAttribute(String mbean, String attribute, String key) throws Exception {
		ObjectName oName = new ObjectName(mbean);
		Object oValue = mBeanServer.getAttribute(oName, attribute);

		if (null == oValue) return "";
		if (null != oValue && oValue instanceof CompositeData) {
			Object value = ((CompositeData)oValue).get(key);
			return value.toString();
		} else {
			return oValue.toString();
		}


	}

	void listBeans(String mbean) throws Exception {

		Set<ObjectName> names = null;
		names = mBeanServer.queryNames(new ObjectName(mbean), null);
		System.out.println("OK - Number of results: " + names.size());
		System.out.println();

		String dump = MBeanDumper.dumpBeans(mBeanServer, names);
		System.out.print(dump);
	}

	public MonitoredMBean[] getMonitoredMBeans() {
		return monitoredMBeans;
	}

	public void setMonitoredMbeans(MonitoredMBean[] monitoredMBeans) {
		this.monitoredMBeans = monitoredMBeans;
	}

	public int getPeriod() {
		return period;
	}

	public void setPeriod(int period) {
		this.period = period;
	}


}

