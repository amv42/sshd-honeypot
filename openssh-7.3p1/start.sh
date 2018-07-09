#!/bin/sh
CURRENT=`pwd`

"$CURRENT/sshd-honeypot" > sshd-honeypot.log 2>&1&
echo $! > sshd-honeypot.pid
exit
