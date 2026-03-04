#include "my_ping.h"
#include <stdio.h>
#include <string.h>

static int	run(int argc, char **argv)
{
	t_ping			p;
	t_icmp_packet	pkt;
	int				pkt_size;
	t_recv_result	res;

	memset(&p, 0, sizeof(p));
	p.sockfd = -1;
	if (parse_args(argc, argv, &p) != 0)
		return (1);
	if (resolve_host(&p) != 0)
		return (1);
	if (create_socket(&p) != 0)
		return (1);
	if (set_socket_options(&p) != 0)
	{
		close_socket(&p);
		return (1);
	}
	debug_opts(&p);
	printf("Resolved: %s -> %s\n", p.host, p.ip_str);
	pkt_size = build_icmp_packet(&p, &pkt, 1);
	debug_icmp_packet(&pkt, pkt_size);
	// TEST: send one packet
	if (send_ping(&p, 1) != 0)
	{
		close_socket(&p);
		return (1);
	}
	printf("Packet sent!\n");
	// TEST: receive one packet
	if (recv_ping(&p, &res) != 0)
	{
		close_socket(&p);
		return (1);
	}
	printf("Packet received: seq=%d, ttl=%d, rtt=%.2fms\n",
		res.seq, res.ttl, res.rtt);
	close_socket(&p);
	return (0);
}

int	main(int argc, char **argv)
{
	return (run(argc, argv));
}
