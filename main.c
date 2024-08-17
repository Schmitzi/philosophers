/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:27 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/08/17 11:13:05 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;

	if (argc == 5 || argc == 6)
	{
		if (arg_checker(argv))
			return (1);
		philo = (t_philo *)malloc(sizeof(t_philo) * atoi(argv[1]));
		if (philo == NULL)
			return (false);
		if (init_all(philo, argv) == false)
			return (free(philo), 1);
		if (thread_init(philo) == false)
			return (destroy_mutex(philo), ft_exit(philo), 1);
		return (destroy_mutex(philo), ft_exit(philo), 0);
	}
	else
		ft_perror("Error: Invalid number of arguments\n");
	return (1);
}
