#include "my_ping.h"
#include <stdio.h>
#include <unistd.h>

static const char	*get_error_msg(int type)
{
	if (type == ICMP_TIME_EXCEEDED)
		return ("Time to live exceeded");
	if (type == ICMP_DEST_UNREACH)
		return ("Destination unreachable");
	return ("Unknown error");
}

void	print_error(t_ping *p, t_recv_result *res)
{
	printf("%d bytes from %s: %s\n",
		res->bytes, res->from_ip, get_error_msg(res->type));
	if (p->opts.verbose)
		print_verbose_error(res);
}

void	print_reply(t_ping *p, t_recv_result *res)
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

void	print_header(t_ping *p)
{
	int	id;

	id = getpid() & 0xFFFF;
	if (p->opts.verbose)
		printf("PING %s (%s): %d data bytes, id 0x%04x = %d\n",
			p->host, p->ip_str, p->opts.size, id, id);
	else
		printf("PING %s (%s): %d data bytes\n",
			p->host, p->ip_str, p->opts.size);
}