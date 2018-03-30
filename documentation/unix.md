## Solaris/SunOS
Commands:  
  /usr/ucb/ps auxww | grep java     : ps long list
  pargs <pid>  
  prtconf | grep Memory
  
Top(Equivalent):

	prstat
    prstat -a
    prstat -s cpu -a -n 8

stat(Equivalent Linux)

    truss -f -v 'lstat,lstat64' ls -d fic.txt | grep "mt ="
	
vi: Terminal too wide

	# stty columns 160
	
* Available, used and free memory in Solaris
```sh
# prtconf | grep Memory
Memory size: 16384 Megabytes
# sar -r 1 1
freemem freeswap
1007947 31669782
# pagesize
8192
# echo 1012114*(8192/1024) | bc -l
8096912
# echo 8096912/1024/1024 | bc -l
7.7GB, Available Memory
```

#### Crontab
The cron service searches its spool area (usually /var/spool/cron/crontabs) for crontab files. Additionally, cron reads the files in /etc/cron.d.

## AIX
