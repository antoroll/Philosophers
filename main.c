/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:59:15 by arolland          #+#    #+#             */
/*   Updated: 2022/01/11 17:09:58 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    display(char *msg, t_philo *philo)
{
    long int    time;

    time = get_time() - philo->data->starting_time;
    pthread_mutex_lock(&philo->data->mutex_print);
    printf(msg, time - time % 10, philo->id + 1);
    pthread_mutex_unlock(&philo->data->mutex_print);
}

long int	get_time(void)
{
	struct timeval	time;
	long int		timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

int	routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->id != 0)
		ft_sleep(100, philo->data);
	while (philo->data->death == 0)
	{
		take_forks(philo);
		start_eating(philo);
		put_forks_down(philo);
		start_sleeping(philo);
		start_thinking(philo);
	}
	return (1);
}

int	create_thread(t_data *data)
{
	mutex_init(data->forks, data->number_of_philo);
	thread_create_philosopher(data->philo);
	check_death(data);
	thread_join(data->philo);
	mutex_destroy(data->forks, data->number_of_philo);
	return (1);
}

void    check_death(t_data *data)
{
    int    i;

    i = 0;
    while (data->death == 0)
    {
        pthread_mutex_lock(&data->mutex_check);
        if (get_time() - data->philo[i].last_meal > data->time_to_die)
        {
            display("%ld %d died\n", &data->philo[i]);
            data->death = 1;
        }
        pthread_mutex_unlock(&data->mutex_check);
        i++;
        if (i == data->number_of_philo)
            i = 0;
        ft_sleep(100, data);
    }
}

int	main(int ac, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		if (get_params(data, argv))
		{
			free(data);
			return (1);
		}
		data->starting_time = get_time();
		data->time = get_time() - data->starting_time;
		philo = malloc(sizeof(t_philo) * data->number_of_philo);
		init_philo(philo, data);
		data->philo = philo;
		init_vars(data);
		create_thread(data);
		free(data->forks);
		free(data);
		free(philo);
	}
	else
		ft_putstr_fd("Wrong number of arguments\n", 2);
	return (0);
}
