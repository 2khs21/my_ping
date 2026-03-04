#include "my_ping_proto.h"
#include <stdio.h>

void	print_usage(void)
{
	fprintf(stderr, "Usage: my_ping [-v] [-?] [-c count] [-i interval] [-p pattern] [-s size] [-T ttl] <host>\n");
}
