#include "my_ping.h"
#include <stdio.h>

static void	print_pattern(unsigned char *pat, int len)
{
	int	i;

	i = 0;
	printf("pattern:     ");
	while (i < len)
		printf("%02x", pat[i++]);
	if (len == 0)
		printf("(none)");
	printf("\n");
}

static void	debug_opts(t_ping *p)
{
	printf("===== DEBUG =====\n");
	printf("host:        %s\n", p->host ? p->host : "(null)");
	printf("ip:          %s\n", p->ip_str[0] ? p->ip_str : "(unresolved)");
	printf("sockfd:      %d\n", p->sockfd);
	printf("verbose:     %d\n", p->opts.verbose);
	printf("count:       %d\n", p->opts.count);
	printf("interval:    %.1f\n", p->opts.interval);
	printf("size:        %d\n", p->opts.size);
	printf("ttl:         %d\n", p->opts.ttl);
	printf("tos:         %d\n", p->opts.tos);
	print_pattern(p->opts.pattern, p->opts.pattern_len);
	printf("=================\n");
}

static void	debug_icmp_packet(t_icmp_packet *pkt, int total_size)
{
	int				i;
	unsigned char	*raw;

	printf("===== ICMP Packet Debug =====\n");
	printf("Type:     %d\n", pkt->hdr.type);
	printf("Code:     %d\n", pkt->hdr.code);
	printf("Checksum: 0x%04x\n", pkt->hdr.checksum);
	printf("ID:       %d\n", pkt->hdr.id);
	printf("Seq:      %d\n", pkt->hdr.seq);
	printf("Size:     %d bytes\n", total_size);
	printf("Timestamp: %ld.%06ld\n",
		pkt->timestamp.tv_sec, pkt->timestamp.tv_usec);
	printf("Raw hex:  ");
	raw = (unsigned char *)pkt;
	i = 0;
	while (i < total_size && i < 32)
		printf("%02x ", raw[i++]);
	if (total_size > 32)
		printf("...");
	printf("\n=============================\n");
}

void	debug_test(t_ping *p)
{
	t_icmp_packet	pkt;
	int				pkt_size;

	debug_opts(p);
	printf("Resolved: %s -> %s\n", p->host, p->ip_str);
	pkt_size = build_icmp_packet(p, &pkt, 1);
	debug_icmp_packet(&pkt, pkt_size);
}
