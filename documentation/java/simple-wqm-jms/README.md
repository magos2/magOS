### Libs for JMS
/opt/mqm/java/lib : jms.jar, com.ibm.mq.jar, com.ibm.mqjms.jar

### Run
java  -cp /opt/mqm/java/lib/jms.jar:/opt/mqm/java/lib/com.ibm.mq.jar:\ 
          /opt/mqm/java/lib/com.ibm.mqjms.jar:. safar/mq/jms/WMQClient

### Refs
- http://kevinboone.net/simplewmqclient.html

