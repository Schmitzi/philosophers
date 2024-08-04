/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:27 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/31 14:59:13 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;

	if (argc == 5 || argc == 6)
	{
		if (arg_checker(argc, argv))
			return (false);
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		if (philo == NULL)
			return (ft_perror("Philo malloc failed"), false);
		if (init_all(philo, argv) == false)
			return (free(philo->thread), free(philo), 1);
		if (thread_init(philo) == false)
			return (destroy_mutex(philo), ft_exit(philo), 1);
		return (destroy_mutex(philo), ft_exit(philo), 0);
	}
	else
		ft_perror("Error: Invalid number of arguments\n");
	return (1);
}
