/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:30:26 by arolland          #+#    #+#             */
/*   Updated: 2022/01/10 18:50:48 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *str)
{
	int				i;
	long int	num;

	i = 0;
	num = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	if (!(s == NULL || fd == 0))
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_sleep(int ms, t_data *data)
{
	int		i;
	_Bool	philo_died;

	i = 100;
	pthread_mutex_lock(&data->mutex_die);
	philo_died = data->death;
	pthread_mutex_unlock(&data->mutex_die);
	while (i < ms && philo_died == FALSE)
	{
		pthread_mutex_lock(&data->mutex_die);
		philo_died = data->death;
		pthread_mutex_unlock(&data->mutex_die);
		usleep(100 * 1000);
		i += 100;
	}
	if (philo_died == FALSE)
		usleep((ms - (i - 100)) * 1000);
}
