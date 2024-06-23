/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:57 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 15:54:26 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	single(t_philo *philo)
{
	pthread_t	thread;

	philo->info->start_time = get_time();
	if (pthread_create(&thread, NULL, &routine, &philo[0]))
		return (ft_error("Single error", philo), 1);
	pthread_detach(thread);
	while (philo->info->dead == 0)
		ft_usleep(0);
	free_exit(philo);
	return (0);
}

void	create_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	philo->info->start_time = get_time();
	while (i < philo->info->num)
	{
		philo[i].id = i + 1;
		philo[i].full = 0;
		philo[i].meals = 0;
		philo[i].state = 0;
		philo[i].final_meal = 0;
		if (i % 2 == 0)
		{
			philo[i].left_fork = &philo->info->forks[i];
			philo[i].right_fork = &philo->info->forks[(i + 1) % \
				philo->info->num];
		}
		else
		{
			philo[i].right_fork = &philo->info->forks[i];
			philo[i].left_fork = &philo->info->forks[(i + 1) % \
				philo->info->num];
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;

	if (argc == 5 || argc == 6)
	{
		if (arg_check(argv))
			return (1);
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (!philo)
			return (ft_error("Error malloc\n", philo));
		if (init_all(philo, argv))
			return (free_exit(philo), 1);
		create_philo(philo);
		if (philo->info->num == 1)
		{
			if (single(philo) == 1)
				return (free_exit(philo), 1);
			return (0);
		}
		if (thread_init(philo) == 1)
			return (free_exit(philo), 1);
		return (free_exit(philo), 0);
	}
	else
		write(2, "Error: Invalid number of arguments\n", 36);
	return (1);
}
