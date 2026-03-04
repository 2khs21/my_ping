#include "my_ping.h"
#include <stdio.h>
#include <unistd.h>

static void	print_reply(t_ping *p, t_recv_result *res)
{
	int	bytes;

	bytes = p->opts.size + ICMP_HDR_SIZE;
	if (res->rtt >= 0)
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
			bytes, p->ip_str, res->seq, res->ttl, res->rtt);
	else
		printf("%d bytes from %s: icmp_seq=%d ttl=%d\n",
			bytes, p->ip_str, res->seq, res->ttl);
}

static void	print_header(t_ping *p)
{
	printf("PING %s (%s): %d data bytes\n",
		p->host, p->ip_str, p->opts.size);
}

static int	ping_once(t_ping *p, int seq)
{
	t_recv_result	res;

	if (send_ping(p, seq) != 0)
		return (1);
	if (recv_ping(p, &res) != 0)
		return (1);
	print_reply(p, &res);
	return (0);
}

int	ping_loop(t_ping *p)
{
	int	seq;
	int	count;

	print_header(p);
	seq = 1;
	count = p->opts.count;
	while (count == 0 || seq <= count)
	{
		ping_once(p, seq);
		seq++;
		if (count == 0 || seq <= count)
			sleep((unsigned int)p->opts.interval);
	}
	return (0);
}
