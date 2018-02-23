### Installion on Ubuntu
    apt install postgresql postgresql-contrib

### Start/Stop
    /etc/init.d/postgresql start

### Access to prompt
    su - postgres
	psql -h /myapp/wrk/sock -p 5432
    psql

    postgres=# \q

### Create a user and database
    su - postgres
    createuser -P -s -e mywiki
    createdb mywikidb

### Nombre de connections ouverts
	select count(*) from pg_stat_activity;