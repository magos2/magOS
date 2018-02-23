#!/usr/bin/python
#===================================================================
#
# Author : Copyright @AR 2017
# Script : use it to monitor your Weblogic performances(Jvm, Jdbc Pool,etc).
#          Tested on Weblogic 12c.
#          WLST is using Jython.
#          see: https://rmohan.com/?p=4576
# Run:
#     java -cp /opt/weblogic/wlserver/server/lib/weblogic.jar weblogic.WLST WeblogicMonitor.py      
#====================================================================
import time as systime, sys, os, traceback
from sys import stdout

sleep_time=10   #seconds
duration  =1    #minutes

# Servers settings
servers='AdminServer'   # servers must be UP
servers=servers.split(',')

adminurl='t3://localhost:7001'   #connect to AdminServer
username='weblogic'
password='weblogic1'

log_dir='./'

# JDBC Pool

# Application

# Threads

# JMS

#---- Function Definitions ------
def conn():
 connect(username,password,adminurl)

#------------------
# JVM Stats 
#------------------
def printJVMHeader(f):
  print>>f, 'Date;HeapFree;HeapSize;HeapFreePercent;HeapSizeMax'
 
def getJVMStats(server,f):
  cd('/ServerRuntimes/'+server+'/JVMRuntime/'+server)
  heapFree=get('HeapFreeCurrent')
  heapSize=get('HeapSizeCurrent')
  heapFreePercent=get('HeapFreePercent')
  heapSizeMax=get('HeapSizeMax')
  timestamp = systime.strftime('%Y-%m-%d %H:%M:%S')
  print>>f, '%s;%d;%d;%d;%d' %(timestamp, heapFree, heapSize, heapFreePercent, heapSizeMax)

#------------------
#  Server state 
#------------------
def getServerState(server):
  try:
    cd('/ServerLifeCycleRuntimes/'+server)
    serverState = cmo.getState()
  except:
    serverState = 'UNKNOWN'
  return serverState;

#------------------
# Reports files 
#------------------
files={}
def openFiles():
  for server in servers:
    f=open(log_dir+'/stats_'+server+'_JVM.csv','w')
    files[server]=f
    printJVMHeader(f)

def closeFiles():
  for server in servers: 
    files[server].close()

#------------------
# MAIN
#------------------
print 'Connecting...'
conn()
domainRuntime()

print 'Begging Weblogic monitoring...'
try:
  openFiles()

  cpt=0
  while cpt<(duration*60):
    for server in servers :
      getJVMStats(server,files[server])
    systime.sleep(sleep_time)
    cpt=cpt+sleep_time
    stdout.write('.')
    stdout.flush() 

except Exception, err:
  print 'Error in Weblogic Monitor'
  traceback.print_exc() 

closeFiles()
print ''
print 'End of monitoring'
exit()

