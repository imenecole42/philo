/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdukuray <gdukuray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:06:54 by gdukuray          #+#    #+#             */
/*   Updated: 2023/01/30 14:21:02 by gdukuray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_mutex_end(t_info *info)
{
	pthread_mutex_lock(&(info->mutex_end));
	{
		if (info->end != 0)
		{
			pthread_mutex_unlock(&(info->mutex_end));
			return (1);
		}
	}
	pthread_mutex_unlock(&(info->mutex_end));
	return (0);
}

int	check_mutex_die(t_info *info)
{
	pthread_mutex_lock(&(info->mutex_die));
	{
		if (info->die != 0)
		{
			pthread_mutex_unlock(&(info->mutex_die));
			return (1);
		}
	}
	pthread_mutex_unlock(&(info->mutex_die));
	return (0);
}

int	check_mutex_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->mutex_end));
	{
		if (philo->numb_times_ate >= info->nb_times_must_eat)
		{
			pthread_mutex_unlock(&(info->mutex_end));
			return (0);
		}
	}
	pthread_mutex_unlock(&(info->mutex_end));
	return (1);
}

int	check_mutex_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->mutex_die));
	{
		if ((get_timestamp_in_ms()
				- philo->t_last_meal) > philo->info->time_to_die)
		{
			pthread_mutex_unlock(&(philo->info->mutex_die));
			return (0);
		}
	}
	pthread_mutex_unlock(&(philo->info->mutex_die));
	return (1);
}
