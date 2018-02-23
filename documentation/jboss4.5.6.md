### Class Loader
By default, Jboss Libs have more priority than ear/war libs. For example if you application contains Hibernate 3.6,
and JBoss has Hibernate 3.3. So Hibernate 3.3 will be loaded. In fact the war Loader demands a it parent(which is JBoss) to load 
hibernate classes. So JBoss will load Hibernate 3.3!  
In Websphere, this precedency is resolved by the parameter PRENT_LAST.

To isolate EAR libs, edit the file  jboss-app.xml  in Ear/META-INFO. see <http://javaetmoi.com/2013/01/isoler-classloader-ear-jboss/>
