#include "my_ping.h"
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>

static void	print_ip_hex(unsigned char *ip_data)
{
	int	i;

	printf("IP Hdr Dump:\n ");
	i = 0;
	while (i < IP_HDR_SIZE)
	{
		printf("%02x%02x ", ip_data[i], ip_data[i + 1]);
		i += 2;
	}
	printf("\n");
}

static void	print_ip_fields_header(void)
{
	printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks");
	printf("      Src      Dst     Data\n");
}

static void	print_ip_fields(unsigned char *ip_data)
{
	struct ip	*ip_hdr;
	char		src[INET_ADDRSTRLEN];
	char		dst[INET_ADDRSTRLEN];

	ip_hdr = (struct ip *)ip_data;
	inet_ntop(AF_INET, &ip_hdr->ip_src, src, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &ip_hdr->ip_dst, dst, INET_ADDRSTRLEN);
	printf(" %d  %d  %02x %04x %04x   %d %04x  %02x  %02x %04x %s  %s \n",
		ip_hdr->ip_v,
		ip_hdr->ip_hl,
		ip_hdr->ip_tos,
		ntohs(ip_hdr->ip_len),
		ntohs(ip_hdr->ip_id),
		(ntohs(ip_hdr->ip_off) >> 13) & 0x7,
		ntohs(ip_hdr->ip_off) & 0x1FFF,
		ip_hdr->ip_ttl,
		ip_hdr->ip_p,
		ntohs(ip_hdr->ip_sum),
		src, dst);
}

static void	print_orig_icmp(unsigned char *ip_data)
{
	struct ip	*ip_hdr;
	t_icmp_hdr	*icmp;
	int			icmp_size;

	ip_hdr = (struct ip *)ip_data;
	icmp = (t_icmp_hdr *)(ip_data + IP_HDR_SIZE);
	icmp_size = ntohs(ip_hdr->ip_len) - IP_HDR_SIZE;
	printf("ICMP: type %d, code %d, size %d, id 0x%04x, seq 0x%04x\n",
		icmp->type, icmp->code,
		icmp_size,
		icmp->id, icmp->seq);
}

void	print_verbose_error(t_recv_result *res)
{
	print_ip_hex(res->orig_ip);
	print_ip_fields_header();
	print_ip_fields(res->orig_ip);
	print_orig_icmp(res->orig_ip);
}