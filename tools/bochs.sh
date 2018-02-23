#!/bin/sh
# 
# -q : silent mode
#

BOCHS_HOME=/logiciels/bochs
export PATH=$PATH:$BOCHS_HOME/bin
bochs -q -rc ./bochs_cmd.txt 
