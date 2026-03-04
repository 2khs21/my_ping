#include "my_ping.h"
#include <stdio.h>
#include <math.h>

void	init_stats(t_stats *s)
{
	s->sent = 0;
	s->received = 0;
	s->min = -1;
	s->max = 0;
	s->sum = 0;
	s->sum_sq = 0;
}

void	update_stats(t_stats *s, double rtt)
{
	if (rtt < 0)
		return ;
	s->received++;
	if (s->min < 0 || rtt < s->min)
		s->min = rtt;
	if (rtt > s->max)
		s->max = rtt;
	s->sum += rtt;
	s->sum_sq += rtt * rtt;
}

static double	calc_mdev(t_stats *s)
{
	double	avg;
	double	variance;

	if (s->received == 0)
		return (0);
	avg = s->sum / s->received;
	variance = (s->sum_sq / s->received) - (avg * avg);
	if (variance < 0)
		variance = 0;
	return (sqrt(variance));
}

void	print_stats(t_ping *p)
{
	int		loss;
	double	avg;

	printf("--- %s ping statistics ---\n", p->host);
	if (p->stats.sent > 0)
		loss = 100 - (p->stats.received * 100 / p->stats.sent);
	else
		loss = 100;
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n",
		p->stats.sent, p->stats.received, loss);
	if (p->stats.received > 0)
	{
		avg = p->stats.sum / p->stats.received;
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
			p->stats.min, avg, p->stats.max, calc_mdev(&p->stats));
	}
}
