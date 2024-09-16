/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:22:24 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/24 12:32:43 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_nbr_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->mutex_end));
	philo->numb_times_ate = philo->numb_times_ate + 1;
	pthread_mutex_unlock(&(philo->info->mutex_end));
}

void	check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->mutex_die));
	philo->t_last_meal = get_timestamp_in_ms();
	pthread_mutex_unlock(&(philo->info->mutex_die));
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	get_sleep(philo->info->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_mutex_die(philo -> info))
	{
		philo_eat((t_philo *)arg);
		if (check_mutex_end(philo->info) || philo->info->nb_philo == 1)
			break ;
		philo_sleep((t_philo *)arg);//des que ils finis de manger il dort
		//(si les autre ils ont finis de mager on appel get sllep pour que il commnce a manger),get sleep pur couper 
		philo_think((t_philo *)arg);
	}
	return (NULL);
}
