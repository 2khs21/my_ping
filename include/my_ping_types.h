#ifndef MY_PING_TYPES_H
# define MY_PING_TYPES_H

# include <netinet/in.h>

typedef struct s_opts
{
	int				verbose;
	int				help;
	int				size;
	int				count;
	double			interval;
	unsigned char	pattern[16];
	int				pattern_len;
	int				ttl;
	int				tos;
}	t_opts;

typedef struct s_ping
{
	char				*host;
	t_opts				opts;
	int					sockfd;
	struct sockaddr_in	addr;
	char				ip_str[INET_ADDRSTRLEN];
}	t_ping;

typedef int	(*t_opt_fn)(int argc, char **argv, int *i, t_ping *p);

typedef struct s_opt_entry
{
	char		opt;
	t_opt_fn	apply;
}	t_opt_entry;

typedef struct s_long_opt_entry
{
	char		*name;
	t_opt_fn	apply;
}	t_long_opt_entry;

#endif