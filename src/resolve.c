#include "my_ping.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>

int	resolve_host(t_ping *p)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	ret = getaddrinfo(p->host, NULL, &hints, &res);
	if (ret != 0)
	{
		fprintf(stderr, "ping: %s: %s\n", p->host, gai_strerror(ret));
		return (1);
	}
	p->addr = *(struct sockaddr_in *)res->ai_addr;
	inet_ntop(AF_INET, &p->addr.sin_addr, p->ip_str, INET_ADDRSTRLEN);
	freeaddrinfo(res);
	return (0);
}
