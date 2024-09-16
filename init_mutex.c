/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdukuray <gdukuray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:57:34 by gdukuray          #+#    #+#             */
/*   Updated: 2023/01/30 16:45:44 by gdukuray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_init(&(info->mutex_forks[i]), NULL))
		{
			write(2, "Init mutex error\n", 18);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_mutex_writing(t_info *info)
{
	if (pthread_mutex_init(&(info->mutex_writing), NULL))
	{
		write(2, "Init mutex error\n", 18);
		return (-1);
	}
	return (0);
}

int	init_mutex_end(t_info *info)
{
	if (pthread_mutex_init(&(info->mutex_end), NULL))
	{
		write(2, "Init mutex error\n", 18);
		return (-1);
	}
	return (0);
}

int	init_mutex_die(t_info *info)
{
	if (pthread_mutex_init(&(info->mutex_die), NULL))
	{
		write(2, "Init mutex error\n", 18);
		return (-1);
	}
	return (0);
}
