/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:20 by schmitzi          #+#    #+#             */
/*   Updated: 2024/06/23 13:56:35 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <time.h>

# define TRUE 1
# define FALSE 0

# define MAX 500

typedef struct s_info
{
	size_t			num;
	size_t			meals;
	size_t			dead;
	size_t			finished;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	died;
	pthread_mutex_t	write;
}	t_info;

typedef struct s_philo
{
	size_t			id;
	size_t			full;
	size_t			state;
	size_t			eat;
	size_t			until_death;
	size_t			meals;
	size_t			final_meal;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_info			*info;
}	t_philo;

// CASE
int			single(t_philo *philo);

// LIBFT
long		ft_atoi(char *nptr);
int			ft_strcmp(char *s1, char *s2);

//ERROR HANDLING
int			ft_error(char *str, t_philo *philo);
int			arg_check(char **argv);
void		free_exit(t_philo *philo);

// INIT
int			init_all(t_philo *philo, char **argv);
void		init_philo(t_philo *philo);
int			thread_init(t_philo *philo);
int			start_mutex(t_philo *philo);
int			init_info(t_philo *philo, char **argv);

// TIME
u_int64_t	get_time(void);
void		ft_usleep(unsigned int microseconds);

// ROUTINE
void		*routine(void *ptr);
void		*monitor(void *ptr);
void		*supervisor(void *ptr);
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

// UTILS
void		messages(char *str, t_philo *philo);

#endif
