/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgeiger- <mgeiger-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:08:25 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/07/17 15:14:07 by mgeiger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <complex.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <time.h>
# include <stdbool.h>
# include <limits.h>

//DEFINES
# define MAX 500

//STRUCTS

typedef struct s_info
{
	size_t			count;
	size_t			meals;
	size_t			dead;
	size_t			til_death;
	size_t			eat_dur;
	size_t			sleep_dur;
	size_t			begin;
	size_t			end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_check;
	pthread_mutex_t	write;
}	t_info;

typedef struct s_philo
{
	size_t				id;
	size_t				state;
	size_t				eat;
	size_t				til_death;
	size_t				meals_eaten;
	size_t				last_meal;
	size_t				stop;
	pthread_t			thread;
	pthread_mutex_t		lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_info				*info;
}	t_philo;

//ARGS
int			arg_checker(char **argv);

//FREE
int			ft_exit(t_philo *philo);
void		ft_perror(char *str);

//INIT
int			init_all(t_philo *philo, char **argv);
int			init_philo(t_philo *philo);
int			init_info(t_philo *philo, char **argv);

//LIBFT
int			ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
long long	ft_atoll(const char *nptr);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int nbr);

//MSG
void		obituary(t_philo *philo);
void		messages(char *str, t_philo *philo, size_t id);

//MUTEX
int			mutex_init(t_philo *philo);
void		destroy_mutex(t_philo *philo);

//ROUTINE
int			dead_end(t_philo *philo);
void		*monitor(void *ptr);
void		*routine(void *ptr);
void		take_forks(t_philo *philo, pthread_mutex_t *left, \
				pthread_mutex_t *right);
void		eat(t_philo *philo);

//THREAD
int			make_threads(t_philo *philo, pthread_t *thread);
int			thread_init(t_philo *philo);

//TIME
void		ft_usleep(t_philo *philo, unsigned int ms);
size_t		check_time(void);

//UTILS
int			death_check(t_philo *philo);
void		form_queue(t_philo *philo);
int			meal_check(t_philo *philo);

int			test(t_philo *philo);

#endif
