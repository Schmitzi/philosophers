/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:00:20 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:00:30 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_philo *philo)
{
	destroy_mutex(philo);
	free(philo->info->forks);
	free(philo->info);
	return (true);
}

void	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
}
