- If using MySQL, create a database ant user
	$ mysql -u root -p
	mysql> create DATABASE wikidb CHARACTER SET 'utf8';
	mysql> GRANT ALL PRIVILEGES ON wikidb.* TO 'wiki'@'localhost' IDENTIFIED BY 'changeit';

- Create DataBase structure
  create_base.sql

- Configure DataSource
  servlet-context.xml

- Create a datasource named: jdbc/wikiDS
  -- For Weblogic
  
  -- For Tomcat
     
     1. ADD to server.xml
     <Resource name="jdbc/wikiDS" auth="Container" type="javax.sql.DataSource"
               maxTotal="100" maxIdle="30" maxWaitMillis="10000"
               username="wiki" password="changeit" driverClassName="com.mysql.jdbc.Driver"
               url="jdbc:mysql://localhost:3306/wikidb"/>

    2. Link datasource to the context(server.xml)
    <Host...>   
      <Context docBase="simple-jee" path="/simple-jee" reloadable="true">
	    <ResourceLink name="jdbc/wikiDS" global="jdbc/wikiDS" type="javax.sql.DataSource"/>
 	  </Context>
 	  
- Access Application Weblogic
  http://localhost:7001/simple-jee/persons