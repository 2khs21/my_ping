#include "my_ping.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RECV_BUF_SIZE	1024

static int	check_echo_reply(unsigned char *buf, ssize_t len, t_recv_result *res)
{
	struct ip	*ip_hdr;
	t_icmp_hdr	*icmp_hdr;
	int			ip_hdr_len;

	ip_hdr = (struct ip *)buf;
	ip_hdr_len = ip_hdr->ip_hl << 2;
	icmp_hdr = (t_icmp_hdr *)(buf + ip_hdr_len);
	if (icmp_hdr->type != ICMP_ECHO_REPLY)
		return (0);
	if (icmp_hdr->id != (uint16_t)getpid())
		return (0);
	res->type = icmp_hdr->type;
	res->seq = icmp_hdr->seq;
	res->ttl = ip_hdr->ip_ttl;
	res->bytes = len - ip_hdr_len;
	inet_ntop(AF_INET, &ip_hdr->ip_src, res->from_ip, INET_ADDRSTRLEN);
	return (1);
}

static int	check_icmp_error(unsigned char *buf, ssize_t len, t_recv_result *res)
{
	struct ip	*ip_hdr;
	struct ip	*orig_ip;
	t_icmp_hdr	*icmp_hdr;
	t_icmp_hdr	*orig_icmp;
	int			ip_hdr_len;

	ip_hdr = (struct ip *)buf;
	ip_hdr_len = ip_hdr->ip_hl << 2;
	icmp_hdr = (t_icmp_hdr *)(buf + ip_hdr_len);
	if (icmp_hdr->type != ICMP_TIME_EXCEEDED
		&& icmp_hdr->type != ICMP_DEST_UNREACH)
		return (0);
	orig_ip = (struct ip *)(buf + ip_hdr_len + ICMP_HDR_SIZE);
	orig_icmp = (t_icmp_hdr *)((unsigned char *)orig_ip + IP_HDR_SIZE);
	if (orig_icmp->id != (uint16_t)getpid())
		return (0);
	res->type = icmp_hdr->type;
	res->code = icmp_hdr->code;
	res->seq = orig_icmp->seq;
	res->ttl = ip_hdr->ip_ttl;
	res->bytes = len - ip_hdr_len;
	memcpy(res->orig_ip, orig_ip, IP_HDR_SIZE + ICMP_HDR_SIZE);

	inet_ntop(AF_INET, &ip_hdr->ip_src, res->from_ip, INET_ADDRSTRLEN);
	return (2);
}

int	recv_ping(t_ping *p, t_recv_result *res)
{
	unsigned char	buf[RECV_BUF_SIZE];
	ssize_t			len;
	int				ret;

	len = recvfrom(p->sockfd, buf, RECV_BUF_SIZE, 0, NULL, NULL);
	if (len < 0)
		return (-1);
	res->rtt = -1.0;
	ret = check_echo_reply(buf, len, res);
	if (ret == 1)
	{
		if (p->opts.size >= (int)TIMESTAMP_SIZE)
			res->rtt = calc_rtt((t_icmp_packet *)(buf + (((struct ip *)buf)->ip_hl << 2)), p->opts.size);
		return (0);
	}
	ret = check_icmp_error(buf, len, res);
	if (ret == 2)
		return (2);
	return (1);
}