#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_error("Time Failed\n");
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned int ms)
{
	struct timeval	start;
	struct timeval	current;
	unsigned int	elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < ms)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000 + \
		(current.tv_usec - start.tv_usec);
	}
}
