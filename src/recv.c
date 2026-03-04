#include "my_ping.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RECV_BUF_SIZE	1024

static int	is_our_reply(unsigned char *buf, ssize_t len)
{
	struct ip		*ip_hdr;
	t_icmp_hdr		*icmp_hdr;
	int				ip_hdr_len;

	if (len < (ssize_t)(sizeof(struct ip) + ICMP_HDR_SIZE))
		return (0);
	ip_hdr = (struct ip *)buf;
	ip_hdr_len = ip_hdr->ip_hl << 2;
	icmp_hdr = (t_icmp_hdr *)(buf + ip_hdr_len);
	if (icmp_hdr->type != ICMP_ECHO_REPLY)
		return (0);
	if (icmp_hdr->id != (uint16_t)getpid())
		return (0);
	return (1);
}

static void	parse_reply(unsigned char *buf, t_ping *p, t_recv_result *res)
{
	struct ip		*ip_hdr;
	t_icmp_hdr		*icmp_hdr;
	int				ip_hdr_len;

	ip_hdr = (struct ip *)buf;
	ip_hdr_len = ip_hdr->ip_hl << 2;
	icmp_hdr = (t_icmp_hdr *)(buf + ip_hdr_len);
	res->seq = icmp_hdr->seq;
	res->ttl = ip_hdr->ip_ttl;
	res->rtt = -1.0;
	if (p->opts.size >= (int)TIMESTAMP_SIZE)
		res->rtt = calc_rtt((t_icmp_packet *)(buf + ip_hdr_len), p->opts.size);
}

int	recv_ping(t_ping *p, t_recv_result *res)
{
	unsigned char	buf[RECV_BUF_SIZE];
	ssize_t			len;

	len = recvfrom(p->sockfd, buf, RECV_BUF_SIZE, 0, NULL, NULL);
	if (len < 0)
	{
		perror("ping: recvfrom");
		return (1);
	}
	if (!is_our_reply(buf, len))
		return (1);
	parse_reply(buf, p, res);
	return (0);
}
