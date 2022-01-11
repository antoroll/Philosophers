/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <arolland@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:08:29 by arolland          #+#    #+#             */
/*   Updated: 2022/01/05 18:29:46 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_parsing(char **argv)
{
	int	i;
	int	j;

	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 0)
	{
		ft_putstr_fd("Too many philosophers\n", 2);
		return (0);
	}
	else if (ft_atoi(argv[1]) == 0)
	{
		ft_putstr_fd("Not enough philosophers\n", 2);
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				ft_putstr_fd("Arguments must be integers\n", 2);
				return (0);
			}
		}
	}
	return (1);
}
