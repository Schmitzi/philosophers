/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:38 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/01 19:53:54 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_philo *philo, char **argv)
{
    size_t  i;

    i = -1;
	philo->info = (t_info *)malloc(sizeof(t_info));
	if (!philo->info)
		return (ft_perror("Error malloc\n"), false);
	if (init_info(philo, argv) == false)
		return (free(philo->info), false);
	while (++i < philo->info->count)
	   philo[i].info = philo->info;
	if (mutex_init(philo) == false)
		return (free(philo->info), false);
	if (init_philo(philo) == false)
		return (destroy_mutex(philo), free(philo->info), false);
	return (true);
}

void	set_forks(t_philo *philo, int i)
{
	if (philo->id % 2 == 0)
	{
		philo[i].right_fork = &philo->info->forks[philo[i].id - 1];
		philo[i].left_fork = &philo->info->forks[(philo[i].id) % \
			philo->info->count];
	}
	else
	{
		philo[i].right_fork = &philo->info->forks[(philo[i].id) % \
			philo->info->count];
		philo[i].left_fork = &philo->info->forks[philo[i].id - 1];
	}
}

int	init_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->info->begin = check_time();
	if (philo->info->begin == 0)
		return (false);
	while (i < philo->info->count)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = philo->info->begin;
		philo[i].stop = false;
		set_forks(philo, i);
		i++;
	}
	return (true);
}

int	too_high(t_philo *philo)
{
	if (philo->info->count > 2147483647 || philo->info->count <= 0)
		return (false);
	if (philo->info->til_death > 2147483647 || philo->info->til_death <= 0)
		return (false);
	if (philo->info->eat_dur > 2147483647 || philo->info->eat_dur <= 0)
		return (false);
	if (philo->info->sleep_dur > 2147483647 || philo->info->sleep_dur <= 0)
		return (false);
	if (philo->info->meals != 18446744073709551615UL && \
		(philo->info->meals > 2147483647 || philo->info->meals == 0))
		return (false);
	return (true);
}

int	init_info(t_philo *philo, char **argv)
{
	philo->info->count = ft_atoi(argv[1]);
	philo->info->til_death = ft_atoi(argv[2]);
	philo->info->eat_dur = ft_atoi(argv[3]);
	philo->info->sleep_dur = ft_atoi(argv[4]);
	if (argv[5])
		philo->info->meals = ft_atoi(argv[5]);
	else
		philo->info->meals = 18446744073709551615UL;
	if (too_high(philo) == false)
		return (ft_perror("Bad input"), false);
	philo->info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (ft_atoi(argv[1])));
	if (philo->info->forks == NULL)
		return (ft_perror("Fork malloc failed"), false);
	philo->info->dead = false;
	philo->info->end = false;
	return (true);
}
