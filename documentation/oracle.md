### Misc

Check driver version

	java -jar ojdbc6.jar -getversion
	you can also view the jdbc version in META-INF/MANIFEST.MF 
	 

### Open Cursor
If error: ORA-01000 maximum open cursors exceeded. see  
 
    # export ORACLE_SID=mySID
	# sqlplus / as sysdba
    sql > show parameter open_cursors
	sql > SELECT value FROM v$parameter WHERE name = 'open_cursors';
	
### Alert Log
	# export ORACLE_SID=mySID
	# sqlplus / as sysdba
    SQL> SET LINESIZE 300
    SQL> COLUMN name  FORMAT A30
    SQL> COLUMN value  FORMAT A30
    SQL> show parameter background

### Statistics
**Last stats**
```
SQL> SELECT table_name, last_analyzed
     FROM user_tables
	 WHERE temporary = 'N' and table_name.like 'JOE%'

SQL> SELECT ui.index_name, ui.last_analyzed
	 FROM user_indexes ui
	 INNER JOIN user_tables ut ON ut.table_name = ui.table_name
	 WHERE ut.temporary = 'N'
```

### Users/Schemas
All users  

    select username from dba_users;

### Check if Database is Open
    > SELECT INSTANCE_NAME, DATABASE_STATUS, INSTANCE_ROLE from v$instance;
    > select open_mode from v$database;
	
### SQLPLUS

### AWR Report
    sqlplus / as sysdba
    SQL> @$ORACLE_HOME/rdbms/admin/awrrpti.sql
	
### Listener 
	su - oracle
	ps -ef | grep lsn
	lsnrctl status SAFAR
	
### Oracle Clustering 
RAC: Real Application Cluster
CRS : Cluster Ready Services

	# su - oracle
	[oracle]>crs_stat -t


How the SCAN adress is configured?
 
	# su - grid
	grid> srvctl config scan

	SCAN name: safar-scan.mydomain.ma, Network: 1/10.02.78.0/255.255.251.0/bond5
	SCAN VIP name: scan1, IP: /safar-scan.mydomain.ma/10.02.79.199
	SCAN VIP name: scan2, IP: /safar-scan.mydomain.ma/10.02.79.198

	grid> nslookup safar-scan.mydomain.ma

	Name:   safar-scan.mydomain.ma
	Address: 10.02.79.198
	Name:   safar-scan.mydomain.ma
	Address: 10.02.79.199

