#include "my_ping.h"
#include <sys/socket.h>
#include <stdio.h>

int	send_ping(t_ping *p, int seq)
{
	t_icmp_packet	pkt;
	int				pkt_size;
	ssize_t			sent;

	pkt_size = build_icmp_packet(p, &pkt, seq);
	sent = sendto(p->sockfd, &pkt, pkt_size, 0,
			(struct sockaddr *)&p->addr, sizeof(p->addr));
	if (sent < 0)
	{
		perror("ping: sendto");
		return (1);
	}
	if (p->opts.verbose)
		printf("Sent %zd bytes to %s (seq=%d)\n", sent, p->ip_str, seq);
	return (0);
}
