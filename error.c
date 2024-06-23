/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:42 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 15:18:56 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_exit(t_philo *philo)
{
	size_t	i;

	if (philo)
	{
		if (philo->info)
		{
			if (philo->info->forks)
			{
				i = 0;
				while (i < philo->info->num)
				{
					pthread_mutex_destroy(&philo->info->forks[i]);
					i++;
				}
				free(philo->info->forks);
				philo->info->forks = NULL;
			}
			pthread_mutex_destroy(&philo->info->write);
			free(philo->info);
			philo->info = NULL;
		}
		if (philo->info && philo->info->num > 0)
		{
			i = 0;
			while (i <= philo->info->num)
			{
				pthread_mutex_destroy(&philo[i].lock);
				i++;
			}
		}
		free(philo);
		philo = NULL;
	}
}


int	ft_error(char *str, t_philo *philo)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	if (philo)
		free_exit(philo);
	return (1);
}
