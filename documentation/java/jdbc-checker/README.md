### Copyright @AR 2017

### About
this is a small tool to help testing connection to a database. you can use it to debug 
jdbc driver, or to stress database by initializing n parallel connections, each can execute n queries.

### HowTO
- unzip jar
- cd jdbc-checker/
- Modify mysql.properties
- for mysql  
  This runs 2 connections, each executes 50 SQL requests
```sh
  java -cp /to/mysql-connector-java-5.1.20-bin.jar:. safar.jdbc.checker.JdbcCheckConnection mysql 2 50  
```  
   
 
- Postgres  
```
  java -cp /path/to/postgresql-42.1.4.jar:. safar.jdbc.checker.JdbcCheckConnection postgresql 2 50
```  

Error: 

> PSQLException: The server does not support SSL.
>Solution:
>comment line in postgresql.properties
>ssl=false
