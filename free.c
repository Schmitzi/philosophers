/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:20 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/17 12:18:20 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	ft_exit(t_philo *philo)
{
	if (philo)
	{
		if (philo->info)
		{
			if (philo->info->forks)
				free(philo->info->forks);
			free(philo->info);
		}
		free(philo);
	}
	return (0);
}

void	stop_threads(pthread_t *threads, size_t i)
{
	while (i)
	{
		if (threads[i])
		{
			pthread_detach(threads[i]);
		}
		i--;
	}
	free(threads);
	threads = NULL;
}

void	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
