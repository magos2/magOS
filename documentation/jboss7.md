## JBoss 7 

#### Installation
an Unzip suffice 

#### Structure and Architecture
- Directory and File Structure
- JBoss Modules
- Server Architecture and Configuration

#### Start/Stop
Start
	
	./standalone.sh
	./standalone.sh -c standalone-ha.xml 
	

Stop

	./jboss-cli.sh --user=jbossadmin --password=Changeit2! --connect --controller=$HOST:9990  command=:shutdown

#### Console, users	
User management

	./add-user.sh

Console
> http://localhost:9990/console

#### JVM Tuning 
- JAVA Options : 
	- standalone in bin/standalone.conf
- Remote JMX with JConsole
	- $JBOSS_HOME/bin/jconsole.sh 
	- and use this url: *service:http:remote+jmx://localhost:9990*
	- this note did not work for me: https://developer.jboss.org/wiki/UsingJconsoleToConnectToJMXOnAS7
     
#### Configuration
##### Standalone
- configuration/standalone.xml 
	- ports: http/8080, management/9990.
	- port-offset: default 0. for example, port-offset=100 gives http port 8180 et console 10090. 

- configuration/standalone-ha.xml: use this configuration to have clustering.
	
Run the standalone with a specefic config file

    ./standalone.sh -c standalone-ha.xml

####  Logging
Configured in **standalone.xml**. the file configuration/logging.properties is only used during JBoss startup. 


