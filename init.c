/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:47 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 15:55:48 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(t_philo *philo)
{
	philo->info = malloc(sizeof(t_info));
	if (!philo->info)
		return (ft_error("Error malloc\n", philo), 1);
	return (0);
}

int	init_all(t_philo *philo, char **argv)
{
	if (alloc(philo))
		return (1);
	if (init_info(philo, argv))
		return (1);
	if (start_mutex(philo))
		return (1);
	return (0);
}

int	init_info(t_philo *philo, char **argv)
{
	philo->info->dead = 0;
	philo->info->finished = 0;
	philo->info->num = ft_atoi(argv[1]);
	philo->info->death_time = ft_atoi(argv[2]);
	philo->info->eat_time = ft_atoi(argv[3]);
	philo->info->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		philo->info->meals = ft_atoi(argv[5]);
	else
		philo->info->meals = -1;
	if (philo->info->num <= 0 || philo->info->death_time <= 0 \
		|| philo->info->eat_time <= 0 || philo->info->sleep_time <= 0)
		return (ft_error("Error init\n", philo));
	philo->info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (ft_atoi(argv[1])));
	if (philo->info->forks == NULL)
		return (ft_error("Error malloc\n", philo), 1);
	return (0);
}

int	start_mutex(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->info->num)
	{
		pthread_mutex_init(&philo->info->forks[i], NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		i++;
	}
	pthread_mutex_init(&philo->info->write, NULL);
	pthread_mutex_init(&philo->info->died, NULL);
	return (0);
}
