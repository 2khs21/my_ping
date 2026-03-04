#include "my_ping.h"
#include <stdio.h>
#include <unistd.h>

static int	ping_once(t_ping *p, int seq)
{
	t_recv_result	res;
	int				ret;

	if (send_ping(p, seq) != 0)
		return (1);
	p->stats.sent++;
	ret = recv_ping(p, &res);
	if (ret == 0)
	{
		update_stats(&p->stats, res.rtt);
		print_reply(p, &res);
	}
	else if (ret == 2)
		print_error(p, &res);
	return (0);
}

int	ping_loop(t_ping *p)
{
	int	seq;
	int	count;

	init_stats(&p->stats);
	print_header(p);
	seq = 0;
	count = p->opts.count;
	while (count == 0 || seq < count)
	{
		ping_once(p, seq);
		seq++;
		if (count == 0 || seq < count)
			sleep((unsigned int)p->opts.interval);
	}
	print_stats(p);
	return (0);
}