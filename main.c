/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:37:27 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/24 12:34:51 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_args(void)
{
	printf("Error : invalid arguments\n");
	exit(1);
}

int	ft_create_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&(info->philo[i].philo_id), NULL, philo_routine,
				&(info->philo[i])))
		{
			printf("Pthread create error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		printf("Error : invalid number of arguments \n");
		return (1);
	}
	if (!ft_atoi(av[1]) || ft_atoi(av[1]) < 0 || ft_atoi(av[1]) > 250
		|| !ft_atoi(av[2]) || ft_atoi(av[2]) < 60 || !ft_atoi(av[3])
		|| ft_atoi(av[3]) < 60 || !ft_atoi(av[4]) || ft_atoi(av[4]) < 60
		|| (av[5] && !ft_atoi(av[5])))
		error_args();
	init_all(&info, av);
	ft_create_philo(&info);
	check_if_philo_is_dead(&info);
	end_philo(&info);/
	return (0);
}
