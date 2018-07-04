# sshd-honeypot

The sshd-honeypot is a modified version of the OpenSSH deamon that forwards commands to Cowrie where all commands are interpreted and returned. The sshd-honeypot is designed to let Cowrie log brute force attacks and the shell interaction performed by the attacker. As the sshd-honeypot uses OpenSSH 

As it 'man-in-the-middles' the connection, it should require minimal changes to make the deamon compatible with other honeypots than Cowrie.


# Installing the sshd-honeypot

* [Step 1: Install cowrie-sshd](#step-1-cowrie-sshd)
* [Step 2: Install dependencies](#step-2-install-dependencies)
* [Step 3: Checkout the code](#step-3-checkout-the-code)
* [Step 4: Run the installer](#step-4-run-the-installer)
* [Step 5: Start the honeypot](#step-5-start-the-honeypot)


## Step 1: Install cowrie-sshd

First we need to install [cowrie-sshd](https://github.com/amv42/cowrie-sshd/blob/master/INSTALL.md). Cowrie-sshd is a modified version of cowrie which functions as backend for the sshd-honeypot to interpret commands and log interactions performed by the attacker.


## Step 2: Install dependencies

On Debian based systems:
```
$ sudo apt-get install build-essential gcc libssh-dev
```


## Step 3: Checkout the code

```
$ git clone https://github.com/amv42/sshd-honeypot
```

## Step 4: Run the installer

The installer will populate all necessary files, configure OpenSSH and install the sshd-honeypot in the current working directory.
```
$ ./install.sh
```

## Step 5: Run the honeypot

```
$ cd openssh-7.3p1
$ ./start.sh
```

By default, the sshd-honeypot will listen on all available IPv4 addresses on port 65222. This can be modified in the sshd_config.
The following firewall rule will forward incoming traffic on port 22 to port 65222.

```
$ sudo iptables -t nat -A PREROUTING -p tcp --dport 22 -j REDIRECT --to-port 65222
```

The sshd-honeypot will connect to Cowrie on 127.0.0.1:65522. You can modify the IPv4 address and port in sshd_config.
