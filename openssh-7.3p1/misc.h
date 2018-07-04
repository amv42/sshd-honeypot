/* $OpenBSD: misc.h,v 1.57 2016/07/15 00:24:30 djm Exp $ */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#ifndef _MISC_H
#define _MISC_H



//===========================================================================
// # sshd-honeypot: add code start
// Most of the variables we need are defined here */

// Redefining variables to avoid name collisions between libssh and openssh
typedef struct Session* Session_sshd_honey;
typedef struct Channel* Channel_sshd_honey;
typedef struct Authctxt* Authctxt_sshd_honey;
typedef struct ssh_channel_struct* ssh_channel_sshd_honey;
typedef struct ssh_session_struct* ssh_session_sshd_honey;

// Stores options for the MasterServer(MS),i.e. Cowrie, parsed by sshd_config
struct sshd_honey_options_defined
{
	int port;                                               // Port
	char ip[256];                                           // IPv4 address
	char username[256];                                     // Username in case specified
	char server_version[256];                               // Server identification string
	int tcpForwardingPort;                                  // Port for port forwarding
	char tcpForwardingHost[256];                            // IPv4 address for port forwarding
};
struct sshd_honey_options_defined sshd_honey_options;


// Stores sshd-cowrie session and channel
struct channel_rw_defined
{
    int type;                                                          // Channel type: 1 = shell, 2 = direct-tcp
    ssh_session_sshd_honey session_data;                               // SSH MS session
    ssh_channel_sshd_honey channel_data;                               // SSH MS channel
    ssh_channel_sshd_honey channel_data_1;                             // SSH MS channel

};
struct channel_rw_defined channel_rw1;                                 // Structure for the SSH MS connection



// Stores details of incoming connections
struct ssh_client_chan_session_defined
{
	ssh_session_sshd_honey initial_session;
    Session_sshd_honey session;             // SSH session
    Channel_sshd_honey channel;             // SSH channel
    char ip[17];                            // IPv4 address
    char port[6];                           // Port number
    char ip_port[23];                       // Stores client IPv4 addresses and ports (SourceID)
    char laddr_lport[23];                   // Stores local Ipv4 address
    int authenticated;                      // Stores if the client is authenticated 0=no, 1=yes
    int to_disconnect;                      // Indicates if the client is to be disconnected 0=no, 1=yes
	int counter_disconnect;                 // Indicates how often we asked to disconnect
    char command[65507];                    // Saves a command from exec request
    int got_command;                        // Indicates an exec request has been received (1/0)
    int rfd;                                // Channel File descriptor to read
	int wfd;                                // Channel File descriptor to write
    int efd;                                // Channel File descriptor extended (escape sequences)
    int s_rfd;                              // Session file descriptor to read
    int s_wfd;                              // Session file descriptor to write
    Authctxt_sshd_honey authctxt;           // Authentication context of the session (must be set to 1 to proceed)
	int s_pid;                              // Pid of session
    int sent_details;                       // Indicates an exec request has been received (1/0)
	char client_version[256];               // Stores the remote client version string
    char target_ip[17];                     // IPv4 address
    char target_port[6];                    // Port number
	char initial_comm[512];                 //Ipv4 address, source port and remote version of clients
	int error;                              // Indicates that something went terribly wrong (e.g. no Connection to Cowrie)
	int subsystem_req;                      // Indicates if a subsystem has been requested


};
struct ssh_client_chan_session_defined ssh_client_conns1[1];

// Functions for the SSH Connection to Cowrie
void start_ssh_ms();
void finish_connection_setup();
int authenticate_password();

// # sshd-honeypot: add code end
//===========================================================================


/* Data structure for representing a forwarding request. */
struct Forward {
	char	 *listen_host;		/* Host (address) to listen on. */
	int	  listen_port;		/* Port to forward. */
	char	 *listen_path;		/* Path to bind domain socket. */
	char	 *connect_host;		/* Host to connect. */
	int	  connect_port;		/* Port to connect on connect_host. */
	char	 *connect_path;		/* Path to connect domain socket. */
	int	  allocated_port;	/* Dynamically allocated listen port */
	int	  handle;		/* Handle for dynamic listen ports */
};

int forward_equals(const struct Forward *, const struct Forward *);

/* Common server and client forwarding options. */
struct ForwardOptions {
	int	 gateway_ports; /* Allow remote connects to forwarded ports. */
	mode_t	 streamlocal_bind_mask; /* umask for streamlocal binds */
	int	 streamlocal_bind_unlink; /* unlink socket before bind */
};

/* misc.c */

char	*chop(char *);
char	*strdelim(char **);
int	 set_nonblock(int);
int	 unset_nonblock(int);
void	 set_nodelay(int);
int	 a2port(const char *);
int	 a2tun(const char *, int *);
char	*put_host_port(const char *, u_short);
char	*hpdelim(char **);
char	*cleanhostname(char *);
char	*colon(char *);
int	 parse_user_host_port(const char *, char **, char **, int *);
long	 convtime(const char *);
char	*tilde_expand_filename(const char *, uid_t);
char	*percent_expand(const char *, ...) __attribute__((__sentinel__));
char	*tohex(const void *, size_t);
void	 sanitise_stdfd(void);
void	 ms_subtract_diff(struct timeval *, int *);
void	 ms_to_timeval(struct timeval *, int);
time_t	 monotime(void);
double	 monotime_double(void);
void	 lowercase(char *s);
int	 unix_listener(const char *, int, int);

void	 sock_set_v6only(int);

struct passwd *pwcopy(struct passwd *);
const char *ssh_gai_strerror(int);

typedef struct arglist arglist;
struct arglist {
	char    **list;
	u_int   num;
	u_int   nalloc;
};
void	 addargs(arglist *, char *, ...)
	     __attribute__((format(printf, 2, 3)));
void	 replacearg(arglist *, u_int, char *, ...)
	     __attribute__((format(printf, 3, 4)));
void	 freeargs(arglist *);

int	 tun_open(int, int);

/* Common definitions for ssh tunnel device forwarding */
#define SSH_TUNMODE_NO		0x00
#define SSH_TUNMODE_POINTOPOINT	0x01
#define SSH_TUNMODE_ETHERNET	0x02
#define SSH_TUNMODE_DEFAULT	SSH_TUNMODE_POINTOPOINT
#define SSH_TUNMODE_YES		(SSH_TUNMODE_POINTOPOINT|SSH_TUNMODE_ETHERNET)

#define SSH_TUNID_ANY		0x7fffffff
#define SSH_TUNID_ERR		(SSH_TUNID_ANY - 1)
#define SSH_TUNID_MAX		(SSH_TUNID_ANY - 2)

/* Fake port to indicate that host field is really a path. */
#define PORT_STREAMLOCAL	-2

/* Functions to extract or store big-endian words of various sizes */
u_int64_t	get_u64(const void *)
    __attribute__((__bounded__( __minbytes__, 1, 8)));
u_int32_t	get_u32(const void *)
    __attribute__((__bounded__( __minbytes__, 1, 4)));
u_int16_t	get_u16(const void *)
    __attribute__((__bounded__( __minbytes__, 1, 2)));
void		put_u64(void *, u_int64_t)
    __attribute__((__bounded__( __minbytes__, 1, 8)));
void		put_u32(void *, u_int32_t)
    __attribute__((__bounded__( __minbytes__, 1, 4)));
void		put_u16(void *, u_int16_t)
    __attribute__((__bounded__( __minbytes__, 1, 2)));

/* Little-endian store/load, used by umac.c */
u_int32_t	get_u32_le(const void *)
    __attribute__((__bounded__(__minbytes__, 1, 4)));
void		put_u32_le(void *, u_int32_t)
    __attribute__((__bounded__(__minbytes__, 1, 4)));

struct bwlimit {
	size_t buflen;
	u_int64_t rate, thresh, lamt;
	struct timeval bwstart, bwend;
};

void bandwidth_limit_init(struct bwlimit *, u_int64_t, size_t);
void bandwidth_limit(struct bwlimit *, size_t);

int parse_ipqos(const char *);
const char *iptos2str(int);
void mktemp_proto(char *, size_t);

/* readpass.c */

#define RP_ECHO			0x0001
#define RP_ALLOW_STDIN		0x0002
#define RP_ALLOW_EOF		0x0004
#define RP_USE_ASKPASS		0x0008

char	*read_passphrase(const char *, int);
int	 ask_permission(const char *, ...) __attribute__((format(printf, 1, 2)));
int	 read_keyfile_line(FILE *, const char *, char *, size_t, u_long *);

#endif /* _MISC_H */
