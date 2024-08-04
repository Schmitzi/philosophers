/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:20 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 15:15:34 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_exit(t_philo *philo)
{
	if (philo->thread)
		free(philo->thread);
    if (philo->info->forks)
        free(philo->info->forks);
    if (philo->info)
        free(philo->info);
    if (philo)
    	free(philo);
    return (true);
}

void	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
