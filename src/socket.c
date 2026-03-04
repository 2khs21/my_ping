#include "my_ping.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

int	create_socket(t_ping *p)
{
	int	sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("ping: socket");
		return (1);
	}
	p->sockfd = sockfd;
	return (0);
}

static int	set_recv_timeout(t_ping *p)
{
	struct timeval	tv;

	tv.tv_sec = (int)p->opts.interval;
	tv.tv_usec = 0;
	if (setsockopt(p->sockfd, SOL_SOCKET, SO_RCVTIMEO,
			&tv, sizeof(tv)) < 0)
	{
		perror("ping: setsockopt RCVTIMEO");
		return (1);
	}
	return (0);
}

int	set_socket_options(t_ping *p)
{
	if (set_recv_timeout(p) != 0)
		return (1);
	if (p->opts.ttl > 0)
	{
		if (setsockopt(p->sockfd, IPPROTO_IP, IP_TTL,
				&p->opts.ttl, sizeof(p->opts.ttl)) < 0)
		{
			perror("ping: setsockopt TTL");
			return (1);
		}
	}
	if (p->opts.tos > 0)
	{
		if (setsockopt(p->sockfd, IPPROTO_IP, IP_TOS,
				&p->opts.tos, sizeof(p->opts.tos)) < 0)
		{
			perror("ping: setsockopt TOS");
			return (1);
		}
	}
	return (0);
}

void	close_socket(t_ping *p)
{
	if (p->sockfd >= 0)
		close(p->sockfd);
}
