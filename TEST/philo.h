#include <complex.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <time.h>
# include <stdbool.h>

//DEFINES
# define MAX 500

//STRUCTS

enum e_state
{
    THINKING,
    EATING,
    SLEEPING,
    DEAD
};

typedef struct s_info
{
	size_t			num_philo;
	size_t			num_meal;
	size_t			dead;
	size_t			til_death;
	size_t			eat_dur;
	size_t			sleep_dur;
	size_t			begin;
	size_t          end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_check;
	pthread_mutex_t	write;
}	t_info;

typedef struct s_philo
{
	size_t			   id;
	size_t			   full;
	size_t			   state;
	size_t			   eat;
	size_t			   til_death;
	size_t			   num_meal;
	size_t		       last_meal;
	size_t             stop;
	pthread_t          thread;
	pthread_mutex_t    lock;
	pthread_mutex_t    *left_fork;
	pthread_mutex_t    *right_fork;
	t_info             *info;
}	t_philo;

//ARGS
int     arg_checker(int argc, char **argv);

//ERROR
void	free_exit(t_philo *philo);

//INIT
int     init_all(t_philo *philo, char **argv);
t_philo *set_values(t_philo *philo, char **argv);
int     init_info(t_philo *philo, char **argv);
void    init_philo(t_philo *philo);

//MUTEX
int     mutex_init(t_philo *philo);

//ROUTINE
void	messages(char *str, t_philo *philo);
void    take_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right);
void    drop_forks(t_philo *philo, pthread_mutex_t *left, pthread_mutex_t *right);
void    *routine(void *ptr);
void    *monitor(void *ptr);
void    *supervisor(void *philo);
void	eat(t_philo *philo);

//THREAD
int thread_init(t_philo *philo);

//TIME
u_int64_t	get_time(void);
void	ft_usleep(t_philo *philo, unsigned int ms);

//UTIL
int     ft_putstr_fd(char *str, int fd);
int     ft_strlen(char *str);
long	ft_atoi(char *nptr);
int	    ft_strcmp(char *s1, char *s2);
void	ft_perror(char *str);


int	ft_error(char *str);
int death_check(t_philo *philo);
void	destroy_mutex(t_philo *philo);
