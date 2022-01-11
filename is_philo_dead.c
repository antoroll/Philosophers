/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_philo_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:03:47 by arolland          #+#    #+#             */
/*   Updated: 2022/01/07 11:57:03 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Bool	is_philo_dead(t_data *data, _Bool *philo_is_dead)
{
	pthread_mutex_lock(&data->mutex_die);
	*philo_is_dead = data->philo_is_dead;
	pthread_mutex_unlock(&data->mutex_die);
	if (*philo_is_dead == TRUE)
		return (TRUE);
	return (FALSE);
}

void	refresh_timestamp(t_philo *philo, struct timeval *timestamp)
{
	pthread_mutex_lock(&philo->data->mutex_die);
	if (philo->state == EAT)
	{
		gettimeofday(timestamp, NULL);
		philo->state = FULL;
	}
	pthread_mutex_unlock(&philo->data->mutex_die);
}

void	is_philo_alive(t_philo *philo, t_data *data,
			struct timeval timestamp, struct timeval end)
{
	long int	timestamp_result;

	pthread_mutex_lock(&data->mutex_die);
	timestamp_result = elapsed_time(timestamp, end);
	if (data->philo_is_dead == FALSE
		&& timestamp_result > data->time_to_die + 2)
	{
		philo->data->philo_is_dead = TRUE;
		print_philo_is_dead(philo);
	}
	pthread_mutex_unlock(&philo->data->mutex_die);
}

int	handle_philos_death(t_philo *philo)
{
	struct timeval	timestamp;
	struct timeval	end;
	_Bool			philo_is_dead;
	t_data			*data;

	data = philo->data;
	philo_is_dead = FALSE;
	gettimeofday(&timestamp, NULL);
	while (philo_is_dead == FALSE
		&& philo->nb_eat < philo->nb_eat)
	{
		gettimeofday(&end, NULL);
		is_philo_dead(data, &philo_is_dead);
		refresh_timestamp(philo, &timestamp);
		is_philo_alive(philo, data, timestamp, end);
	}
	return (1);
}
