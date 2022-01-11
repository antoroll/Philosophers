/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:08:22 by arolland          #+#    #+#             */
/*   Updated: 2022/01/05 18:19:47 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(pthread_mutex_t *mutex, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
			return (1);
	}
	return (0);
}

int	mutex_destroy(pthread_mutex_t *mutex, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_destroy(&mutex[i]) != 0)
			return (1);
	}
	return (0);
}
