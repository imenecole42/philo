/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_or_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:13:56 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/24 12:37:09 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].philo_id, NULL))//permet a main principal d'attendre il se termine pas apre la routine
			return (1);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_destroy(&(info->mutex_forks[i])))//destrure tout les mutex
			return (2);
		i++;
	}
	if (pthread_mutex_destroy(&(info->mutex_writing)))
		return (2);
	if (pthread_mutex_destroy(&(info->mutex_end)))
		return (2);
	if (pthread_mutex_destroy(&(info->mutex_die)))
		return (2);
	return (0);
}

void	change_end(t_info *info)
{
	pthread_mutex_lock(&(info->mutex_end));
	if (info->one_philo_has_finish == info->nb_philo)
		info->end = 1;
	pthread_mutex_unlock(&(info->mutex_end));
}

void	change_die(t_philo *philo)
{
	pthread_mutex_lock(&(philo -> info->mutex_writing));
	if (check_mutex_last_meal(philo) == 0)
	{
		print_status_die(philo, "died");
		philo -> info->die = 1;
	}
	pthread_mutex_unlock(&(philo -> info->mutex_writing));
	usleep(2);
}

void	check_if_philo_is_dead(t_info *info)//verifier est ce que 
{
	int	i;

	while (check_mutex_end(info) == 0)
	{
		i = 0;
		if (check_mutex_die(info) == 0 && i < info->nb_philo)
		{
			change_die(&info -> philo[i]);
			i++;
		}
		if (info->die)
			break ;
		i = 0;
		if (info->nb_times_must_eat > 0 && i < info->nb_philo
			&& check_mutex_eat(info, &info->philo[i]) == 0)
		{
			pthread_mutex_lock(&(info->mutex_end));
			info->one_philo_has_finish++;
			i++;
			pthread_mutex_unlock(&(info->mutex_end));
		}
		change_end(info);
	}
}
