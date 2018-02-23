#!/bin/sh

#if [[ "$ret" -ne "0" ]]
#then
#   ifup eth0
#fi

git add -A
git commit -a -m "commit"
git push origin master
