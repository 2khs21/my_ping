#include "my_ping_proto.h"
#include "my_ping_consts.h"

static int	hex_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

static int	parse_hex_pair(const char *s, int *j, unsigned char *out)
{
	int	hi;
	int	lo;

	hi = hex_digit(s[(*j)++]);
	if (hi < 0)
		return (1);
	if (s[*j])
	{
		lo = hex_digit(s[(*j)++]);
		if (lo < 0)
			return (1);
	}
	else
	{
		lo = hi;
		hi = 0;
	}
	*out = (unsigned char)((hi << 4) | lo);
	return (0);
}

static int	parse_pattern(const char *s, unsigned char *buf, int *len)
{
	int	i;
	int	j;

	if (!s || !s[0])
		return (1);
	i = 0;
	j = 0;
	while (s[j] && i < MAX_PATTERN_LEN)
	{
		if (parse_hex_pair(s, &j, &buf[i++]) != 0)
			return (1);
	}
	*len = i;
	return (0);
}

int	opt_pattern(int argc, char **argv, int *i, t_ping *p)
{
	if ((*i + 1) >= argc)
		return (1);
	if (parse_pattern(argv[*i + 1], p->opts.pattern, &p->opts.pattern_len) != 0)
		return (1);
	*i = *i + 1;
	return (0);
}
