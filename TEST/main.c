#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;

	if (argc == 5 || argc == 6)
	{
		if (arg_checker(argc, argv))
			return (false);
	    philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!philo)
	        return (ft_putstr_fd("Error malloc\n", 2), false);
		if (init_all(philo, argv) == false)
			return (false);
		if (thread_init(philo) == false)
		    return (free_exit(philo), false);
		return (free_exit(philo), true);
	}
	else
	    ft_putstr_fd("Error: Invalid number of arguments\n", 2);
	return (true);
}
