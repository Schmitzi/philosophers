/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:38 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 15:59:28 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_philo *philo, char **argv)
{
	philo->info = (t_info *)malloc(sizeof(t_info));
	if (!philo->info)
		return (ft_perror("Error malloc\n"), false);
	if (init_info(philo, argv) == false)
		return (free(philo->info), false);
	if (mutex_init(philo) == false)
		return (free(philo->info), false);
	if (init_philo(philo) == false)
		return (destroy_mutex(philo), free(philo->info), false);
	return (true);
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
		i++;
	}
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
		philo->info->meals = -1;
	if (philo->info->count <= 0 || philo->info->til_death <= 0 \
		|| philo->info->eat_dur <= 0 || philo->info->sleep_dur <= 0)
		return (ft_perror("Init failed"), false);
	philo->info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (ft_atoi(argv[1])));
	if (philo->info->forks == NULL)
		return (ft_perror("Fork malloc failed"), false);
	philo->info->dead = false;
	philo->info->end = false;
	return (true);
}
