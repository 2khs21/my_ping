#include "my_ping.h"
#include <stdio.h>
#include <string.h>

static int	run(int argc, char **argv)
{
	t_ping	p;

	memset(&p, 0, sizeof(p));
	p.sockfd = -1;
	if (parse_args(argc, argv, &p) != 0)
		return (1);
	if (resolve_host(&p) != 0)
		return (1);
	if (create_socket(&p) != 0)
		return (1);
	if (set_socket_options(&p) != 0)
	{
		close_socket(&p);
		return (1);
	}
	debug_opts(&p);
	printf("Resolved: %s -> %s\n", p.host, p.ip_str);
	// TODO: ping loop
	close_socket(&p);
	return (0);
}

int	main(int argc, char **argv)
{
	return (run(argc, argv));
}
