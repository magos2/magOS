package safar.mq.jms;

import javax.jms.Message;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueReceiver;
import javax.jms.QueueSender;
import javax.jms.QueueSession;
import javax.jms.Session;

import com.ibm.mq.jms.MQQueue;
import com.ibm.mq.jms.MQQueueConnectionFactory;
import com.ibm.msg.client.wmq.WMQConstants;

/**
 * Simple point to point Websphere MQ using JMS
 *
 */
public class WMQClient
{
	static String hostname = "192.168.56.101";
	static int    port     = 1414;
	static String queueManager = "QM_ORANGE";
	static String channel = "MY.JMS.SVRCONN";
	static String user = "wlsadm"; //OS user, must be a member off mqm group. user mqm is forbidden. 
	static String password = "changeit";
	
	public static void main (String[] args) throws Exception {

		System.out.println("Connecting to "+hostname+":"+port+" QM="+queueManager+
									", channel="+channel+", user="+user+", password="+password);
		
		MQQueueConnectionFactory qcf = new MQQueueConnectionFactory();

		// Config
		qcf.setHostName (hostname);
		qcf.setPort (port);
		qcf.setQueueManager (queueManager);
		qcf.setChannel (channel);

		// Although there are many possible values of transport type,
		//  only 'client' and 'bindings' work in a Java client. Bindings
		//  is a kind of in-memory transport and only works when the client
		//  and the queue manager are on the same physical host. In most
		//  cases we need 'client'. 
		qcf.setTransportType (WMQConstants.WMQ_CM_CLIENT);

		// In a default setup of W-MQ, the password is not checked. The
		//   only auth check is that the user ID is an O/S user that is
		//   a member of the mqm group. 'mqm' itself is forbidden
		//   unless specifically allowed
		QueueConnection qc = qcf.createQueueConnection (user, password);
		qc.start();

		// --- Everything below this line is generic JMS code ---

		// Create a queue and a session
		Queue q = new MQQueue("Q1");
		QueueSession s = qc.createQueueSession (false, Session.AUTO_ACKNOWLEDGE);

		// Create and send a TextMessage 
		QueueSender qs = s.createSender (q);
		Message m = s.createTextMessage ("Salam!");
		qs.send (m);

		// Create a QueueReceiver and wait for one message to be delivered
		QueueReceiver qr = s.createReceiver (q);
		Message m2 = qr.receive();

		System.out.println ("Received message: " + m); 

		s.close();
		qc.close();
	}
}
