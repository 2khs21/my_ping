#include "my_ping_proto.h"

int	opt_verbose(int argc, char **argv, int *i, t_ping *p)
{
	(void)argc;
	(void)argv;
	(void)i;
	p->opts.verbose = 1;
	return (0);
}

int	opt_help(int argc, char **argv, int *i, t_ping *p)
{
	(void)argc;
	(void)argv;
	(void)i;
	p->opts.help = 1;
	return (0);
}
