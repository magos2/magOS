### Installation
```sh
  apt install mysql-server
```

### Start/Stop
With service:
```sh
 service mysql start|stop|status|reload|restart
```

Without service

    ./mysqld --defaults-file=~/my.cnf
	./mysqladmin --defaults-file=~/my.cnf -u root -p   shutdown
	


### Config file
```sh
/etc/mysql/mysql.conf.d/mysqld.cnf

  [mysqld]
  #
  # * Basic Settings
  #
  user            = mysql
  pid-file        = /var/run/mysqld/mysqld.pid
  socket          = /var/run/mysqld/mysqld.sock
  port            = 3306
  basedir         = /usr
  datadir         = /var/lib/mysql
  tmpdir          = /tmp
```

### Logs
```sh
/var/log/mysql/error.log
```

Activer les logs debug : show SQL requests
```
# mysql -u root -p

mysql> SHOW VARIABLES LIKE "general_log%";

+------------------+----------------------------------------------------------------------------------------+
| Variable_name    | Value                                                                                  |
+------------------+----------------------------------------------------------------------------------------+
| general_log      | OFF                                                                                    |
| general_log_file | /var/MySQL/mysql-5.6.25-linux-glibc2.5-x86_64/data/mysql_p.log                         |
+------------------+----------------------------------------------------------------------------------------+

mysql> SET GLOBAL general_log = 'ON';

```


### Console GUI
* mysql-workbench
```sh
   apt install mysql-workbench
```
* Tora
```sh
  apt install tora libqt4-sql-mysql 
```
* mysqladmin (win)
* phpmyadmin

### Coonection to database 
```sh
$ mysql -u root -p

mysql> show databases;
mysql> use HELLODB;
mysql> show tables;
mysql> desc TABLE-NAME;
mysql> show columns from TABLE-NAME;

mysql> ALTER TABLE message MODIFY error_description VARCHAR(500) ;
```

### Create&Delete a base
```sh
mysql> create DATABASE hellodb CHARACTER SET 'utf8';
mysql> drop DATABASE hellodb;
mysql> show databases;
```

### Manage a User 
Create a User
```sh
$ mysql -u root -p

mysql> GRANT ALL PRIVILEGES ON mywikidb.* TO 'mywiki'@'localhost' IDENTIFIED BY 'changeit';
```

Change Password  
```sh
mysql> use mywikidb;
mysql> SET PASSWORD FOR 'mywiki'@'localhost' = PASSWORD('changeit');
```

### Reset root password
```sh
# mysqld --skip-grant-tables &
# mysql
mysql> FLUSH PRIVILEGES;
mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'system';
mysql> exit
```

### Errors
1. mysqld --skip-grant-tables : Could not create unix socket lock file /var/run/mysqld/mysqld.sock.lock
```sh
sudo mkdir /var/run/mysqld; sudo chown mysql /var/run/mysqld
```

### Create database
```sh
mysql> GRANT ALL PRIVILEGES ON *.* TO mywiki@localhost
    ->   IDENTIFIED BY 'changeit' WITH GRANT OPTION;
mysql> create database mywikidb;
mysql> use mywikidb;
mysql> create table USER (
    ->   id int not null auto_increment primary key,
    ->   firstname varchar(25),lastname varchar(25));
```

Add to _context.xml_ or _server.xml_ in Tomcat:
```sh
       <Resource name="jdbc/hellodb" auth="Container" type="javax.sql.DataSource"
               maxTotal="100" maxIdle="30" maxWaitMillis="10000"
               username="mywiki" password="changeit" driverClassName="com.mysql.jdbc.Driver"
               url="jdbc:mysql://localhost:3306/mywikidb"/> 
```






