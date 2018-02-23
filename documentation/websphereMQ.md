### Commands MQ

	$ dspmqver				; display the version of MQ
	$ dspmq					; check status of queue managers
	$ endmqm -i QM_ORANGE	; shutdown immediate of qm

### Installation of Websphere MQ
----
At a minimum, you must install the MQSeriesRuntime and the MQSeriesServer.

Environnement

    Websphere MQ 8
    Ubuntu 16.04
    see: http://www-01.ibm.com/support/docview.wss?uid=swg21656068

Log in as root

Prepare the machine

    groupadd mqm
    useradd -g mqm -m -d /opt/mqm mqm
    passwd mqm

Install rpm for Ubuntu
  
    apt install rpm

Create the licence

    ./mqlicense.sh -text_only


Installation, default dir /opt/mqm

    ; install MQSeriesRuntime before other packages
    rpm -ivh --nodeps --force-debian MQSeriesRuntime*.rpm
    rpm -ivh --nodeps --force-debian MQSeriesServer*.rpm 
    rpm -ivh --nodeps --force-debian MQSeriesJRE*.rpm MQSeriesJava*.rpm MQSeriesAMS-*.rpm
    rpm -ivh --nodeps --force-debian MQSeriesExplorer*.rpm
    /opt/mqm/bin/setmqinst -i -p /opt/mqm   ; set this as default installation 

! No Java found: for MQ Explorer

    cd /opt/mqm/java/jre64
    tar xvfz mq_jre64.tar.gz

To uninstall WebsphereMQ
    
    rpm -qa | grep MQSeries | xargs rpm -ev  
    rm -rf /usr/mqm /var/mqm /opt/mqm

### MQ Explorer
----
Installation

    rpm -ivh --nodeps --force-debian MQSeriesExplorer-*.rpm 


Install as Plugin in Eclipse

    Eclipse : Kepler 4.3.2
    Plugin eclipse must be installed: GEF
    Pugin archive: /opt/mqm/mqexlorer/eclipse/MQExplorerSDK.zip

open the perspective *MQ Explorer* :
[see this](https://www.ibm.com/support/knowledgecenter/en/SSFKSJ_8.0.0/com.ibm.mq.explorer.doc/
                e_install_in_eclipse.htm)


Connect MQ Exlorer to a remote queue


	DEFINE CHANNEL(SYSTEM.ADMIN.SVRCONN) CHLTYPE(SVRCONN)

	useradd -g web mqadm
	SET CHLAUTH(SYSTEM.ADMIN.SVRCONN) TYPE(BLOCKUSER) USERLIST('nobody')
	SET CHLAUTH(SYSTEM.ADMIN.SVRCONN) TYPE(USERMAP) CLNTUSER(abrahali) USERSRC(MAP) MCAUSER(mqadm)
	REFRESH security

	DISPLAY CHLAUTH(*)
	
### Queue Manager
----
Connect using user **mqm**

#### Create a Queue Manager

    crtmqm  QM_ORANGE
    
#### Files

    qm.ini: /var/mqm/qmgrs/QM_ORANGE/qm.ini
    /var/mqm	gestionnaire et files
    /var/mqm/log	logs des gestionnaires	
	/usr/lpp/mqm	code MQSERIES AIX
    /opt/mqm	code MQSERIES HP-UX ou Sun Solaris


#### Logs
Windows: C:\Program Files\IBM\WebSphere MQ\log\qmgr

UNIX: /var/mqm/log/
     /var/mqm/errors/AMQERR01.LOG

#### Start/Start Queue Manager

    strmqm QM_ORANGE
    endmqm QM_ORANGE

    $ ps -ef | grep mqm
      mqm      13934  2298   /opt/mqm/bin/amqzxma0 -m QM_ORANGE -u mqm


#### Create a Local Queue
    runmqsc QM_ORANGE
    define qlocal (Q1)

#### Display QMGR

    dspmq


#### Start MQSC for queue manager QMGR1

    runmqsc QM_ORANGE


#### Create a Test Queue

    define qlocal(TESTQ)
    display qlocal(TESTQ)
    end


Send and Read a message: using Sample programs(**MQSeriesAMS-*.rpm**)

    cd samp/bin/
    ./amqsput TESTQ QM_ORANGE  ; put message test in queue 
    ./amqsbcg TESTQ QM_ORANGE  ; display headers
    ./amqsget TESTQ QM_ORANGE  ; get and remove message from queue


#### Listener

    runmqsc QM_ORANGE
    
    DEFINE LISTENER(QM_ORANGE.lsnr) TRPTYPE(tcp) PORT(1414) IPADDR(192.168.93.107)
    START LISTENER(QM_ORANGE.lsnr)
    end    
    
    ps -ef | grep runmqlsr
    mqm       3135  2643 /opt/mqm/bin/runmqlsr -r -m QM_ORANGE -t TCP -p 1414 -i 192.168.93.107
    
    ; to delete a listener
    DELETE LISTENER(QM_ORANGE.lsnr)

Stop/Start Listener

	display LISTENER(*)
	START LISTENER(QM_ORANGE.lsnr)


	runmqlsr -m QM_ORANGE -t TCP -p 1414
    endmqlsr -m QM_ORANGE

Same listener can service multiple queue managers,
	
#### Channel 
Communication between queue managers relies on a channel. A channel is uni-directional; a second channel is required to return data.

The server-connection channel, called SYSTEM.ADMIN.SVRCONN,must exist on every remote queue manager 
you need to manage using MQ explorer 

    display CHANNEL(SYSTEM.DEF.SVRCONN)
	display CHANNEL(*)
	
    DEFINE CHANNEL(SYSTEM.ADMIN.SVRCONN) CHLTYPE(SVRCONN)
    start channel(SYSTEM.ADMIN.SVRCONN)

    DEFINE CHANNEL(MYAPP.JMS.SVRCONN) CHLTYPE(SVRCONN)
    start channel(MYAPP.JMS.SVRCONN)

    end
    
	
#### DISPLAY
```
$ runmqsc QM_ORANGE
DISPLAY

DISPLAY QM_ORANGE 
   QMNAME(QM_ORANGE)                       ACCTCONO(DISABLED)
   ACCTINT(1800)                           ACCTMQI(OFF)
   CRDATE(2017-10-24)                      CRTIME(22.27.40)
   MAXMSGL(4194304)                        MAXPROPL(NOLIMIT)
   MAXPRTY(9)                              MAXUMSGS(10000)
   ...

dis qmgr
   
display LISTENER(*)	
display LISTENER(QM_ORANGE.lsnr)

display CHANNEL(SYSTEM.DEF.SVRCONN)
display CHANNEL(*)
	
```

#### Authentication
There are 2 auth types(AUTHTYPE attribute):
* IDPWOS: the queue manager uses the local operating system to authenticate the user ID and password.
* IDPWLDAP: the queue manager uses an LDAP server to authenticate the user ID and password. 

```
display qmgr CONNAUTH

DISPLAY CHLAUTH(*)
   CHLAUTH(SYSTEM.ADMIN.SVRCONN)           TYPE(USERMAP)
   CLNTUSER(ABSAFAR)                       MCAUSER(MQADMIN)
   

ALTER QMGR CONNAUTH(SYSTEM.DEFAULT.AUTHINFO.IDPWOS)
     DEFINE AUTHINFO(SYSTEM.DEFAULT.AUTHINFO.IDPWOS) +
     AUTHTYPE(IDPWOS) +
     FAILDLAY(10) +
     CHCKLOCL(OPTIONAL) +
     CHCKCLNT(REQUIRED)

REFRESH SECURITY TYPE(CONNAUTH)


```

setmqaut -m MYQMGR -t qmgr -p myuser +connect +inq +dsp

setmqaut -m QM_ORANGE -t qmgr -p safar +connect +inq +dsp

setmqaut -m QM_ORANGE -n Q1 -t q -g mqm +get +put +browse +inq

setmqaut -m QM_ORANGE -n Q1 -t q -g mqm +get +put +browse +inq

Dump authorisation

	dmpmqaut -m QM_ORANGE                        ;dump all 
	dmpmqaut -m QM_ORANGE -n MYAPP.JMS.SVRCONN   ;dump a profile(ie channel) auth
	
	
-- https://engineeernitesh.blogspot.fr/2017/02/mq-error-2035-mqrcnotauthorized-or.html

#### Authorization
https://webspheremqadministrator.blogspot.fr/2014/06/how-to-configure-websphere-mq.html
    
    $ setmqaut -m QM_ORANGE -n a.* -t queue -p anass +all
    
    $ runmqsc QM_ORANGE
    DISPLAY CHLAUTH(*)
    
    
### Miscs
Problem MQExplorer: Access no permitted. You are not authorised to perform this operation. (AMQ4036)  
    $ runmqsc QM_ORANGE
    SET CHLAUTH(*) TYPE(BLOCKUSER) USERLIST('nobody','*MQADMIN')
    SET CHLAUTH(SYSTEM.ADMIN.*) TYPE(BLOCKUSER) USERLIST('nobody')
see: <http://www-01.ibm.com/support/docview.wss?uid=swg21577137>


Convert rpm to deb using **alien**: /!\ not compatible with websphere mq

    apt install alien
    sudo alien *.rpm

## Tutorial: Create the MQ objects for connectivity on a Linux server
Check the version of MQ:
	
	$ dspmqver

Create the QM_ORANGE  queue managers

	crtmqm QM_ORANGE	

Start the QM_ORANGE  queue managers:
	
	strmqm QM_ORANGE	


Check the status of the queue managers:

	$ dspmq	-m QM_ORANGE
	
Create the required objects under the QM_ORANGE queue manager:

	$ runmqsc QM_ORANGE	
	
	Define the local queue:
	DEFINE QL(Q1.IN.QL)
	
	Define the channel:
	DEFINE CHANNEL(MY.JMS.SVRCONN) CHLTYPE(SVRCONN)
	
	Define the listeners:
	DEFINE LISTENER(QM_ORANGE.LIS) TRPTYPE(TCP) PORT(1414) CONTROL(QMGR)
	
	Start the listener:
	START LISTENER(QM_ORANGE.LIS)
	
Create the client-connection channel for QM_ORANGE  queue manager:
	
	DEFINE CHANNEL(MY.JMS.SVRCONN) CHLTYPE(CLNTCONN) CONNAME('192.168.56.101(1414)') QMNAME(QM_ORANGE)

Provide the authorizations for the QM_ORANGE queue manager for the Integration node to connect to the queue manager:
	useradd -g web -G mqm wlsadm
	setmqaut -m QM_ORANGE -t qmgr -p wlsadm +connect
	setmqaut -m QM_ORANGE -n Q1.IN.QL -t q -p wlsadm +inq +get

Ensure that all authorizations reflect the queue manager that is being used:
		
	REFRESH SECURITY		
	
	
- See: https://www.ibm.com/developerworks/websphere/library/techarticles/1602_movva-trs/1602_Movva.html
	
	
	
## Docs
----
- WQM tutos: https://www.ibm.com/support/knowledgecenter/en/SSFKSJ_7.5.0/com.ibm.mq.explorer.doc/bi00112_.htm
- https://webspheremqadministrator.blogspot.fr/2014/06/part-iv-websphere-mq-interview-questions.html
- https://webspheremqadministrator.blogspot.fr/2014/06/how-to-configure-websphere-mq.html
- Ref: https://www.ibm.com/support/knowledgecenter/en/SSFKSJ_8.0.0/com.ibm.mq.pro.doc/q001010_.htm
- Install WMQ: https://www.ibm.com/support/knowledgecenter/en/SSFKSJ_8.0.0/com.ibm.mq.explorer.doc/bi00258_.htm
- https://webspheremq.wordpress.com/category/mq-administration/tutorials/
- [Case Study](http://www.webspheretools.com/sites/webspheretools.nsf/docs/
      mq%20tutorial.%20mq%20intercommunication.%20queue%20local%20and%20queue%20remote%20example!opendocument)

