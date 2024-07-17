#include "philo.h"

int	ft_error(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	return (1);
}
