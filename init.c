/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:01:55 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/24 12:39:45 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].info = info;
		info->philo[i].num = i + 1;
		info->philo[i].philo_i = i;
		info->philo[i].l_fork = i;
		info->philo[i].numb_times_ate = 0;
		info->philo[i].t_last_meal = info->start;
		if (i == 0)
			info->philo[i].r_fork = info->nb_philo - 1;
		else
			info->philo[i].r_fork = i - 1;
		i++;
	}
	return (0);
}

void	ft_init_info(t_info *info, char **av)
{
	int	i;

	i = 0;
	while (i < 250)
	{
		info->fork_status[i] = 0;//attribue a chaque fourchette un statut9notion a comprendre det_lok statut=0)
		i++;//initiolise statut
	}
	info->nb_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]) * 1000;
	info->time_to_eat = ft_atoi(av[3]) * 1000;
	info->time_to_sleep = ft_atoi(av[4]) * 1000;
	info->start = get_timestamp_in_ms();
	info->nb_times_must_eat = 0;
	info->one_philo_has_finish = 0;
	info->end = 0;//quand il arrette
	info->die = 0;//quand il morts
	if (av[5])
	{
		info->nb_times_must_eat = ft_atoi(av[5]);
		if (info->nb_times_must_eat < 1)
			error_args();
	}
}

int	init_all(t_info *info, char **av)
{
	ft_init_info(info, av);
	init_philo(info);
	if (init_mutex_writing(info) < 0 || init_mutex_forks(info) < 0
		|| init_mutex_end(info) < 0 || init_mutex_die(info) < 0)
		exit(1);
	return (0);
}
