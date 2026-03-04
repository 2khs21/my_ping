#include "my_ping_proto.h"
#include "my_ping_consts.h"

static void	init_parse(t_ping *p)
{
	p->host = 0;
	p->opts.verbose = 0;
	p->opts.help = 0;
	p->opts.size = DEFAULT_SIZE;
	p->opts.count = DEFAULT_COUNT;
	p->opts.interval = DEFAULT_INTERVAL;
	p->opts.ttl = DEFAULT_TTL;
	p->opts.pattern_len = 0;
	p->opts.tos = DEFAULT_TOS;
}

static int	fail_usage(void)
{
	print_usage();
	return (1);
}

static int	finalize_parse(t_ping *p)
{
	if (p->opts.help)
	{
		print_usage();
		return (0);
	}
	if (!p->host)
		return (fail_usage());
	return (0);
}

int	parse_args(int argc, char **argv, t_ping *p)
{
	int	i;

	i = 1;
	init_parse(p);
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			if (dispatch_opt(argc, argv, &i, p) != 0)
				return (fail_usage());
		}
		else if (!p->host)
			p->host = argv[i];
		else
			return (fail_usage());
		i++;
	}
	return (finalize_parse(p));
}
