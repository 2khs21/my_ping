#ifndef MY_PING_ICMP_H
# define MY_PING_ICMP_H

# include <stdint.h>
# include <sys/time.h>

# define ICMP_ECHO_REQUEST	8
# define ICMP_ECHO_REPLY	0
# define ICMP_TIME_EXCEEDED	11
# define ICMP_DEST_UNREACH	3

# define ICMP_HDR_SIZE		8
# define IP_HDR_SIZE		20
# define TIMESTAMP_SIZE		sizeof(struct timeval)

typedef struct s_icmp_hdr
{
	uint8_t		type;
	uint8_t		code;
	uint16_t	checksum;
	uint16_t	id;
	uint16_t	seq;
}	t_icmp_hdr;

typedef struct s_icmp_packet
{
	t_icmp_hdr		hdr;
	struct timeval	timestamp;
	unsigned char	padding[1500];
}	t_icmp_packet;

#endif