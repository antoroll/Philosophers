/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:08:27 by arolland          #+#    #+#             */
/*   Updated: 2022/01/10 18:23:44 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_params(t_data *data, char **argv)
{
	if (!check_parsing(argv))
		return (1);
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->flag = 0;
	data->death = 0;
	if (argv[5])
		data->number_of_eating = ft_atoi(argv[5]);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philo);
	return (0);
}

int	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		philo[i].data = data;
		philo[i].philo_is_dead = FALSE;
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->number_of_philo;
		philo[i].state = -1;
		philo[i].nb_eat = 0;
		philo[i].last_meal = get_time();
		i++;
	}
	return (0);
}

void	init_vars(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_check, NULL);
	pthread_mutex_init(&data->mutex_eating, NULL);
	pthread_mutex_init(&data->mutex_die, NULL);
}
