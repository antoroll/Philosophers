/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:08:24 by arolland          #+#    #+#             */
/*   Updated: 2022/01/10 17:48:43 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create_philosopher(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].data->number_of_philo)
	{
		if (pthread_create(&(philo[i]).philo, NULL,
			(void *) routine, (void *) &philo[i]) != 0)
		return (0);
	}
	philo->data->flag = 1;
	return (1);
}

int	thread_join(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->number_of_philo)
	{
		if (pthread_join(philo[i].philo, NULL))
			return (0);
	}
	return (1);
}
