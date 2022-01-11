/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:55:52 by arolland          #+#    #+#             */
/*   Updated: 2022/01/10 18:51:25 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0
# define FULL 0
# define EAT 3
# define SLEEPING 2
# define STARVING 1

typedef struct s_philo {
	pthread_t		philo;
	int				id;
	int				left_fork;
	int				right_fork;
	unsigned int	nb_eat;
	long int		last_meal;
	int				state;
	_Bool			philo_is_dead;
	struct s_data	*data;
	struct s_time	*heure;
}	t_philo;

typedef struct s_data {
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				number_of_philo;
	int				number_of_eating;
	_Bool 			death;
	long int		starting_time;
	long int		time;
	int				flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_check;
	struct s_philo	*philo;
	struct s_time	*heure;
}	t_data;

int				get_params(t_data *data, char **argv);
long int		ft_atoi(const char *str);
void			ft_putstr_fd(char const *s, int fd);
int				check_parsing(char **argv);
void			ft_putchar_fd(char c, int fd);
int				init_philo(t_philo *philo, t_data *data);
int				mutex_init(pthread_mutex_t *mutex, int size);
int				mutex_destroy(pthread_mutex_t *mutex, int size);
int				routine(void *philosopher);
int				thread_join(t_philo *philo);
int				thread_create_philosopher(t_philo *philo);
int				take_forks(t_philo *philo);
int				start_eating(t_philo *philo);
int				start_thinking(t_philo *philo);
int				start_sleeping(t_philo *philo);
int				put_forks_down(t_philo *philo);
int				get_params(t_data *data, char **argv);
int				handle_philos_death(t_philo *philo);
void			is_philo_alive(t_philo *philo, t_data *data,
					struct timeval timestamp, struct timeval end);
void			refresh_timestamp(t_philo *philo, struct timeval *timestamp);
_Bool			is_philo_dead(t_data *data, _Bool *philo_is_dead);
void			ft_sleep(int ms, t_data *data);
void			init_vars(t_data *data);
long int		get_time(void);
void			display(char *msg, t_philo *philo);
void			check_death(t_data *data);
void			ft_sleep(int ms, t_data *data);

#endif