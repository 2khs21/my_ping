#include "my_ping_proto.h"
#include "my_ping_consts.h"

int	opt_size(int argc, char **argv, int *i, t_ping *p)
{
	int	n;

	if ((*i + 1) >= argc)
		return (1);
	if (parse_u32(argv[*i + 1], &n) != 0)
		return (1);
	if (n > MAX_SIZE)
		return (1);
	p->opts.size = n;
	*i = *i + 1;
	return (0);
}

int	opt_count(int argc, char **argv, int *i, t_ping *p)
{
	int	n;

	if ((*i + 1) >= argc)
		return (1);
	if (parse_u32(argv[*i + 1], &n) != 0)
		return (1);
	if (n <= 0)
		return (1);
	p->opts.count = n;
	*i = *i + 1;
	return (0);
}

int	opt_interval(int argc, char **argv, int *i, t_ping *p)
{
	int	n;

	if ((*i + 1) >= argc)
		return (1);
	if (parse_u32(argv[*i + 1], &n) != 0)
		return (1);
	p->opts.interval = (double)n;
	*i = *i + 1;
	return (0);
}

int	opt_ttl(int argc, char **argv, int *i, t_ping *p)
{
	int	n;

	if ((*i + 1) >= argc)
		return (1);
	if (parse_u32(argv[*i + 1], &n) != 0)
		return (1);
	if (n < 1 || n > 255)
		return (1);
	p->opts.ttl = n;
	*i = *i + 1;
	return (0);
}

int	opt_tos(int argc, char **argv, int *i, t_ping *p)
{
	int	n;

	if ((*i + 1) >= argc)
		return (1);
	if (parse_u32(argv[*i + 1], &n) != 0)
		return (1);
	if (n < 0 || n > 255)
		return (1);
	p->opts.tos = n;
	*i = *i + 1;
	return (0);
}
