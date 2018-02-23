### Apache 2.4
Install directory:
  /etc/apache2/

Enable/disable a module(Debian)
  a2enmod ssl
  a2dismod ssl

### Check Syntax
	/apache/bin/httpd -f httpd.conf -t
	/apache/bin/httpd -f httpd.conf -S
	
### Configuration HTTPS

LoadModule ssl_module modules/mod_ssl.so


Include conf/safar.com-ssl.conf

Listen safar192:443
<VirtualHost *:443>
    ServerName ar.safar.com
    SSLEngine on
    SSLCertificateFile "/path/to/www.mysafar.com.pem"
    SSLCertificateKeyFile "/path/to/www.mysafar.com.key"
</VirtualHost>



### Rediriger HTTP vers HTTPS 

```sh
Activate le mod_rewrite
On Debian
 $ a2enmod rewrite
On others:
 LoadModule rewrite_module modules/mod_rewrite.so



<VirtualHost *:80>
  ServerName www.mysafar.com

  RewriteEngine On
  RewriteCond %{HTTPS} off
  RewriteRule (.*) https://%{HTTP_HOST}%{REQUEST_URI} [L,R=301] 
</VirtualHost>

ar.safar.com_ssl.conf:
<VirtualHost *:443>
  ServerName www.mysafar.com
  ...
</VirtualHost>

Ou bien si plusieurs domaines

```


### Page de Maintenance
Ajouter un virtual host de maintenance. En remplacement le VHost d'origine.

vhost_mnt.conf
```
<VirtualHost 10.0.0.35>
    ServerName www.mysafar.com
    DocumentRoot /www/data/html
    RewriteEngine on
    RewriteCond %{REQUEST_URI} !.*(npg|gif|jpg)$
    RewriteRule ^/.* /maintenance_mysafar.html
    ErrorLog /logs/maintenance_error_log
    CustomLog /logs/maintenance_access_log combined
</VirtualHost>
```

Puis recharger la conf:
	
	mv vhost_app.conf vhost_app.conf.ORIGIN
	cp vhost_mnt.conf vhost_app.conf
    apachectl reload

### Virtual Host pour Weblogic
	<VirtualHost x.x.x.x>
    ServerName www.application.domaine.fr
     <IfModule mod_weblogic.c>
        WebLogicCluster
               wls1.application.domaine.fr:port,wls2.application.domaine.fr:port
        <Location />
                SetHandler weblogic-handler
        </Location>
    </IfModule>
    ErrorLog /appli/log/application_error_log
    CustomLog /appli/log/application_access_log combined
	</VirtualHost>


### Erreur: [warn] VirtualHost overlaps with VirtualHost , the first has precedence
Ajouter:

	NameVirtualHost 10.168.1.10:80
	NameVirtualHost 10.168.1.10:443

	<VirtualHost 10.168.1.10:80>
	....
	
	<VirtualHost 10.168.1.10:443>
	....
	
	
## Quick php5 installation on Gnuroot Debian 
** Install apache/php5
   # apt install apache2 php5 libapache2-mod-php5
** verify php installed version
   # apt show php5
** Verify that "php.conf" and "php.load" are enabled
   # ls -l /etc/apache2/mods-enabled
   see http://wiki.goldzoneweb.info/installation_de_php_5_pour_apache_2
** create file "infos.php" under /var/www/html, with content
   <?php phpinfo(); ?>
** chmod 744 infos.php
** http://127.0.0.1:2080/infos.php
** Docs
   - Installation php5: http://wiki.goldzoneweb.info/installation_de_php_5_pour_apache_2
