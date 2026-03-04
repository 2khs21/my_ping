#include "my_ping_proto.h"
#include <string.h>

static const t_opt_entry	g_opt_tab[] = {
	{'v', opt_verbose},
	{'?', opt_help},
	{'s', opt_size},
	{'c', opt_count},
	{'i', opt_interval},
	{'p', opt_pattern},
	{'T', opt_tos},
	{0, 0}
};

static const t_long_opt_entry	g_long_opt_tab[] = {
	{"ttl", opt_ttl},
	{"verbose", opt_verbose},
	{"help", opt_help},
	{0, 0}
};

static int	dispatch_long_opt(int argc, char **argv, int *i, t_ping *p)
{
	int			j;
	const char	*name;

	name = argv[*i] + 2;
	j = 0;
	while (g_long_opt_tab[j].name)
	{
		if (strcmp(name, g_long_opt_tab[j].name) == 0)
			return (g_long_opt_tab[j].apply(argc, argv, i, p));
		j++;
	}
	return (1);
}

static int	dispatch_short_opt(int argc, char **argv, int *i, t_ping *p)
{
	int	j;

	j = 0;
	while (g_opt_tab[j].opt)
	{
		if (argv[*i][1] == g_opt_tab[j].opt && argv[*i][2] == '\0')
			return (g_opt_tab[j].apply(argc, argv, i, p));
		j++;
	}
	return (1);
}

int	dispatch_opt(int argc, char **argv, int *i, t_ping *p)
{
	if (argv[*i][1] == '-')
		return (dispatch_long_opt(argc, argv, i, p));
	return (dispatch_short_opt(argc, argv, i, p));
}
