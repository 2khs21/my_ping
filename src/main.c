#include "my_ping.h"
#include <stdio.h>
#include <string.h>

static int	run(int argc, char **argv)
{
	t_ping	p;

	memset(&p, 0, sizeof(p));
	if (parse_args(argc, argv, &p) != 0)
		return (1);
	debug_opts(&p);
	return (0);
}

int	main(int argc, char **argv)
{
	return (run(argc, argv));
}
