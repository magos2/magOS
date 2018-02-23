#!/bin/sh
# A simple web aspirator using wget
#
SITE=http://wiki.osdev.org
DOMAINS=.osdev.org
DEPTH=2
FILTER=
AGENT=Firefox
TRIES=3
DEST_DIR=/sdcard/ABR/sites/
OPTS='-r -k -np --continue --no-verbose --page-requisites --convert-links --adjust-extension --force-html -e robots=off  --timestamping --no-use-server-timestamps'

wget $OPTS -l $DEPTH  --directory-prefix=$DEST_DIR -t $TRIES --user-agent=$AGENT --domains=$DOMAINS $SITE

#save properly a single page
#wget -E -H -k  -p http://<site>/<document>

