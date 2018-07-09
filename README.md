# sshd-honeypot

The sshd-honeypot is a modified version of the OpenSSH deamon that forwards commands to Cowrie where all commands are interpreted and returned. The sshd-honeypot is designed to let Cowrie log brute force attacks and the shell interaction performed by the attacker. As the sshd-honeypot uses OpenSSH, it can not be fingerprinted based on protocol deviations or differences in error messages.
```
+------------+     +-------------+     +------------+  
|  Attacker  |<--->|sshd-honeypot|<--->|   Cowrie   |  
|            |     |  (OpenSSH)  |     |            |  
+------------+     +-------------+     +------------+  
```


# Installing the sshd-honeypot

* [Step 1: Install cowrie-sshd](#step-1-install-cowrie-sshd)
* [Step 2: Install dependencies](#step-2-install-dependencies)
* [Step 3: Checkout the code](#step-3-checkout-the-code)
* [Step 4: Run the installer](#step-4-run-the-installer)
* [Step 5: Start the honeypot](#step-5-start-the-honeypot)


## Step 1: Install cowrie-sshd

First we need to install [cowrie-sshd](https://github.com/amv42/cowrie-sshd/blob/master/INSTALL.md). Cowrie-sshd is a modified version of Cowrie which functions as backend for the sshd-honeypot to interpret commands and log interactions performed by the attacker.


## Step 2: Install dependencies

On Debian based systems:
```
$ sudo apt-get install build-essential gcc libssh-dev
```


## Step 3: Checkout the code

```
$ git clone https://github.com/amv42/sshd-honeypot
Cloning into 'sshd-honeypot'...
remote: Counting objects: 744, done.
remote: Compressing objects: 100% (661/661), done.
remote: Total 744 (delta 78), reused 739 (delta 76), pack-reused 0
Receiving objects: 100% (744/744), 1.76 MiB | 0 bytes/s, done.
Resolving deltas: 100% (78/78), done.
Checking connectivity... done.

$ cd sshd-honeypot
```

## Step 4: Run the installer

The installer will populate all necessary files and configure/install the sshd-honeypot in the current working directory.
```
$ ./install.sh
```

## Step 5: Start the honeypot

```
$ cd openssh-7.3p1
$ ./start.sh
```

By default, the sshd-honeypot will listen on all available IPv4 addresses on port 65222. This can be modified in the sshd_config.
The following firewall rule will forward incoming traffic on port 22 to port 65222.

```
$ sudo iptables -t nat -A PREROUTING -p tcp --dport 22 -j REDIRECT --to-port 65222
```

The sshd-honeypot will connect to Cowrie on 127.0.0.1:65522. You can modify the IPv4 address and port in the sshd_config.
