#include "philo.h"

int init_all(t_philo *philo, char **argv)
{
    philo->info = (t_info *)malloc(sizeof(t_info));
    if (!philo->info)
        return (ft_error("Error malloc\n"), false);
    if (init_info(philo, argv) == false)
        return (false);
    if (mutex_init(philo) == false)
        return (false);
    init_philo(philo);
   return (true);
}

void    init_philo(t_philo *philo)
{
    size_t i;

    i = 0;
    philo->info->begin = get_time();
    while (i < philo->info->num_philo)
    {
        philo[i].id = i + 1;
        philo[i].full = 0;
        philo[i].num_meal = 0;
        philo[i].state = 0;
        philo[i].last_meal = 0;
        if (i % 2 == 0)
        {
            philo[i].left_fork = &philo->info->forks[i];
            philo[i].right_fork = &philo->info->forks[(i + 1) % philo->info->num_philo];
        }
        else
        {
            philo[i].right_fork = &philo->info->forks[i];
            philo[i].left_fork = &philo->info->forks[(i + 1) % philo->info->num_philo];
        }
        i++;
    }
}

int init_info(t_philo *philo, char **argv)
{
    philo->info->dead = 0;
    philo->info->finished = 0;
    philo->info->num_philo = ft_atoi(argv[1]);
    philo->info->til_death = ft_atoi(argv[2]);
    philo->info->eat_dur = ft_atoi(argv[3]);
    philo->info->sleep_dur = ft_atoi(argv[4]);
    if (argv[5])
    philo->info->num_meal = ft_atoi(argv[5]);
    else
        philo->info->num_meal = -1;
    if (philo->info->num_philo <= 0 || philo->info->til_death <= 0 \
		|| philo->info->eat_dur <= 0 || philo->info->sleep_dur <= 0)
		return (ft_error("Error init\n"), false);
	philo->info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (ft_atoi(argv[1])));
	if (philo->info->forks == NULL)
		return (ft_error("Error malloc\n"), false);
	return (true);
}
