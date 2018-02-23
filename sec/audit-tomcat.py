#!/usr/bin/python3.5
# -*- coding: utf-8 -*-

from lxml import etree
import os

# Tomcat 8
serverXml = './tomcat_server.xml'
outHTML = 'tomcat_audit.html'

def out (s):
  fout.write(s+"\n")
  return  

def header ():
  out('<!DOCTYPE html>')
  out('<html>')
  out('<head>')
  out('<title>Tomcat8 Audit</title>')
  out('''
  <style>
  table {
    border-collapse: collapse;
    width: 100%;
  }
  th, td {
    text-align: left;
    padding: 8px;
  }
  tr:nth-child(even){background-color: #f2f2f2}
  th {
    background-color: #4CAF50;
    color: white;
  }
  </style>
  ''')
  out('</head>')
  out('<body>')
  return

def footer ():
  out('</body>')
  out('</html>')
  fout.close()
  return 

def message(level, problem, action):
  out('<table style="width:80%">')
  out('''
  <tr>
    <th>Level</th>
    <th>Problem</th>
    <th>Action</th>
  </tr>
  ''')
  out('<tr>')
  out(' <td> '+level+'</td>')
  out(' <td> '+problem+'</td>')
  out(' <td> '+action+'</td>')
  out('</tr>')
  out('</table>')
  return 

def audit():
  tree = etree.parse(serverXml)
  server = tree.getroot()
  shutdownPort = server.get('port')
  if shutdownPort != -1:
    message ('Warn',
             'Setting the port attribute to -1 disables the shutdown port',
             'If the shutdown port is not disabled, a strong password should be configured for shutdown')
  for connector in tree.xpath('/Server/Service/Connector'):
    print(connector.get('port'))
  return

#
# MAIN
#
fout = open(outHTML,'w') 
header()
audit()
footer()











