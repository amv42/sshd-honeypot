#!/bin/bash
sudo ln -s /usr/lib/x86_64-linux-gnu/libssh.so /usr/lib/x86_64-linux-gnu/libssh_new.so
CURRENT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd openssh-7.3p1
EXEC_BUILD="${CURRENT}/openssh-7.3p1/configure --prefix=${CURRENT}/openssh-7.3p1/opt --sysconfdir=${CURRENT}/openssh-7.3p1/sys --without-pam --without-shadow"
sudo $EXEC_BUILD
make
make install
