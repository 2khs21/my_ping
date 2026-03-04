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

void	debug_opts(t_ping *p)
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