#include "my_ping.h"
#include <string.h>

static int	init_ping(t_ping *p, int argc, char **argv)
{
	memset(p, 0, sizeof(*p));
	p->sockfd = -1;
	if (parse_args(argc, argv, p) != 0)
		return (1);
	if (resolve_host(p) != 0)
		return (1);
	if (create_socket(p) != 0)
		return (1);
	if (set_socket_options(p) != 0)
	{
		close_socket(p);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_ping	p;
	int		ret;

	if (init_ping(&p, argc, argv) != 0)
		return (1);
	debug_test(&p);
	ret = ping_loop(&p);
	close_socket(&p);
	return (ret);
}
