package safar.tomcat.monitor;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.bind.annotation.XmlAccessType;

import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVPrinter;
import org.apache.logging.log4j.Level;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.core.LoggerContext;
import org.apache.logging.log4j.core.appender.ConsoleAppender;
import org.apache.logging.log4j.core.config.builder.api.AppenderComponentBuilder;
import org.apache.logging.log4j.core.config.builder.api.ComponentBuilder;
import org.apache.logging.log4j.core.config.builder.api.ConfigurationBuilder;
import org.apache.logging.log4j.core.config.builder.api.ConfigurationBuilderFactory;
import org.apache.logging.log4j.core.config.builder.api.LayoutComponentBuilder;
import org.apache.logging.log4j.core.config.builder.impl.BuiltConfiguration;


@XmlAccessorType(XmlAccessType.FIELD)
public class MonitoredMBean {
	static String SEPARATOR = ";";
	static String NEW_LINE  = "\n";

	@XmlAttribute
	String name;

	@XmlAttribute
	String logger;

	@XmlElement(name="attribute")
	Attribute[] attributes;


	@XmlTransient
	String logdir;

	@XmlAccessorType(XmlAccessType.FIELD)
	static class Attribute {
		@XmlAttribute
		String name;

		@XmlElement(name="key")
		String[] keys;	
	};

	public void writeHead() {
		logdir = System.getProperty("catalina.base") + "/logs/";
		FileWriter fileWriter = null;
		CSVPrinter csvPrinter = null;
		CSVFormat csvFormat = CSVFormat.DEFAULT.withRecordSeparator(NEW_LINE);
		ArrayList<String> head = new ArrayList<>();
		for (Attribute attribute : attributes) {
			if (null != attribute.keys)
				for (String key: attribute.keys)
					head.add(attribute.name + "." + key);
			else
				head.add(attribute.name);
		}
		//csvFormat.withHeader(head.toArray(a));
		try {

			fileWriter = new FileWriter(logdir + logger);
			csvPrinter = new CSVPrinter(fileWriter, csvFormat);

			csvPrinter.printRecord(head);
		} catch (Exception e) {
			System.out.println("Error in writeValues !!!");
			e.printStackTrace();
		} finally {
			try {
				fileWriter.flush();
				fileWriter.close();
				csvPrinter.close();
			} catch (IOException e) {
				System.out.println("Error while flushing/closing fileWriter/csvPrinter !!!");
				e.printStackTrace();
			}
		}
	}
	

	public void writeValues(ArrayList<String> values) {
		FileWriter fileWriter = null;
		CSVPrinter csvPrinter = null;
		CSVFormat csvFormat = CSVFormat.DEFAULT.withRecordSeparator(NEW_LINE);

		try {
			fileWriter = new FileWriter(logdir + logger, true);
			csvPrinter = new CSVPrinter(fileWriter, csvFormat);
			csvPrinter.printRecord(values);
		} catch (Exception e) {
			System.out.println("Error in writeValues !!!");
			e.printStackTrace();
		} finally {
			try {
				fileWriter.flush();
				fileWriter.close();
				csvPrinter.close();
			} catch (IOException e) {
				System.out.println("Error while flushing/closing fileWriter/csvPrinter !!!");
				e.printStackTrace();
			}
		}

	}


	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	
	public String getLogger() {
		return logger;
	}

	public void setLogger(String logger) {
		this.logger = logger;
	}

}
