/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:08:19 by arolland          #+#    #+#             */
/*   Updated: 2022/01/10 19:00:06 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
	if (philo->data->death == 0)
		display("%ld %d has taken a fork\n", philo);
	return (1);
}

int	start_eating(t_philo *philo)
{
	if (philo->data->death == 0)
		display("%ld %d is eating\n", philo);
	pthread_mutex_lock(&philo->data->mutex_eating);
	philo->last_meal = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->mutex_eating);
	ft_sleep(philo->data->time_to_eat, philo->data);
	return (1);
}

int	start_thinking(t_philo *philo)
{
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
	{
		if (philo->data->death == 0)
			display("%ld %d is thinking\n", philo);
	}
	return (1);
}

int	start_sleeping(t_philo *philo)
{
	if (philo->data->death == 0)
		display("%ld %d is sleeping\n", philo);
	ft_sleep(philo->data->time_to_sleep, philo->data);
	return (1);
}

int	put_forks_down(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	return (1);
}
