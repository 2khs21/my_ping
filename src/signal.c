#include "my_ping.h"
#include <signal.h>
#include <stdlib.h>

static t_ping	*g_ping = NULL;

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_ping)
	{
		print_stats(g_ping);
		close_socket(g_ping);
	}
	exit(0);
}

void	setup_signals(t_ping *p)
{
	g_ping = p;
	signal(SIGINT, sigint_handler);
}
