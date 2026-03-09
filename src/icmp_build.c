#include "my_ping.h"
#include "my_ping_icmp.h"
#include <string.h>
#include <unistd.h>

static void	fill_pattern(unsigned char *buf, int len, t_ping *p)
{
	int	i;
	int	plen;

	plen = p->opts.pattern_len;
	i = 0;
	while (i < len)
	{
		if (plen > 0)
			buf[i] = p->opts.pattern[i % plen];
		else
			buf[i] = (unsigned char)(i + 0x10);
		i++;
	}
}

static void	init_icmp_hdr(t_icmp_hdr *hdr, int seq)
{
	hdr->type = ICMP_ECHO_REQUEST;
	hdr->code = 0;
	hdr->id = (uint16_t)getpid();
	hdr->seq = (uint16_t)seq;
	hdr->checksum = 0;
}

static void	fill_payload(t_icmp_packet *pkt, t_ping *p)
{
	int	payload_size;
	int	padding_len;

	payload_size = p->opts.size;
	if (payload_size >= (int)TIMESTAMP_SIZE)
	{
		gettimeofday(&pkt->timestamp, NULL);
		padding_len = payload_size - TIMESTAMP_SIZE;
	}
	else
		padding_len = payload_size;
	if (padding_len > 0)
		fill_pattern(pkt->padding, padding_len, p);
}

int	build_icmp_packet(t_ping *p, t_icmp_packet *pkt, int seq)
{
	int	total_size;

	total_size = ICMP_HDR_SIZE + p->opts.size;
	memset(pkt, 0, sizeof(*pkt));
	init_icmp_hdr(&pkt->hdr, seq);
	fill_payload(pkt, p);
	pkt->hdr.checksum = checksum(pkt, total_size);
	return (total_size);
}
