#include "my_ping.h"
#include "my_ping_icmp.h"

uint16_t	checksum(void *data, int len)
{
	uint16_t	*buf;
	uint32_t	sum;

	buf = (uint16_t *)data;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(uint8_t *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return ((uint16_t)(~sum));
}

double	calc_rtt(t_icmp_packet *pkt, int payload_size)
{
	struct timeval	now;
	double			rtt;

	if (payload_size < (int)TIMESTAMP_SIZE)
		return (-1.0);
	gettimeofday(&now, NULL);
	rtt = (now.tv_sec - pkt->timestamp.tv_sec) * 1000.0;
	rtt += (now.tv_usec - pkt->timestamp.tv_usec) / 1000.0;
	return (rtt);
}
