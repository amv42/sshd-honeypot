#!/bin/sh
PIDFILE=sshd.pid
CURRENT=`pwd`
cd $(dirname $0)
PID=$(cat $PIDFILE 2>/dev/null)
PID=$((PID+1))
if [ -n "$PID" ]; then
  echo "Stopping sshd-Server...\n"
  kill -TERM $PID
fi

"$CURRENT/sshd" > logging.log 2>&1&
echo $! > sshd.pid
exit




