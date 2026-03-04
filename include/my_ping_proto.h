#ifndef MY_PING_PROTO_H
# define MY_PING_PROTO_H

# include "my_ping_types.h"
# include "my_ping_icmp.h"

void	debug_test(t_ping *p);

int		parse_args(int argc, char **argv, t_ping *p);
void	print_usage(void);

int		dispatch_opt(int argc, char **argv, int *i, t_ping *p);

int		opt_verbose(int argc, char **argv, int *i, t_ping *p);
int		opt_help(int argc, char **argv, int *i, t_ping *p);
int		opt_size(int argc, char **argv, int *i, t_ping *p);
int		opt_count(int argc, char **argv, int *i, t_ping *p);
int		opt_interval(int argc, char **argv, int *i, t_ping *p);
int		opt_ttl(int argc, char **argv, int *i, t_ping *p);
int		opt_pattern(int argc, char **argv, int *i, t_ping *p);
int		opt_tos(int argc, char **argv, int *i, t_ping *p);

int		parse_u32(const char *s, int *out);

int		resolve_host(t_ping *p);
int		create_socket(t_ping *p);
int		set_socket_options(t_ping *p);
void	close_socket(t_ping *p);

uint16_t	checksum(void *data, int len);
int			build_icmp_packet(t_ping *p, t_icmp_packet *pkt, int seq);
double		calc_rtt(t_icmp_packet *pkt, int payload_size);

int		send_ping(t_ping *p, int seq);
int		recv_ping(t_ping *p, t_recv_result *res);

int		ping_loop(t_ping *p);

void	init_stats(t_stats *s);
void	update_stats(t_stats *s, double rtt);
void	print_stats(t_ping *p);
void	setup_signals(t_ping *p);

#endif