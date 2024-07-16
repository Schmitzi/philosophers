#include "philo.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_philo			philo[MAX];

	if (argc == 5 || argc == 6)
	{
		if (arg_checker(argc, argv))
			return (false);
		if (init_all(philo, argv) == false)
			return (false);
		if (thread_init(philo) == false)
		    return (destroy_mutex(philo), free(philo->info->forks), false);
		return (destroy_mutex(philo), free(philo->info->forks), true);
	}
	else
	    ft_putstr_fd("Error: Invalid number of arguments\n", 2);
	return (true);
}
