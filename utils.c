/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:06:52 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/24 12:11:25 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}

int	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);//la date est jour et heure
	return ((tv.tv_sec) * 1000000 + (tv.tv_usec));//tranformer em ml seconde *1000000
}

void	print_status(t_philo *philo, char *str)//pour afficher le temp dans terminal
{
	pthread_mutex_lock(&(philo->info->mutex_writing));
	if (!check_mutex_die(philo->info))
	{
		printf("%d ", (get_timestamp_in_ms() - philo->info->start) / 1000);
		printf("%d ", philo->num);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo->info->mutex_writing));
}

void	print_status_die(t_philo *philo, char *str)
{
	printf("%d ", (get_timestamp_in_ms() - philo->info->start) / 1000);
	printf("%d ", philo->num);
	printf("%s\n", str);
}

void	get_sleep(int time)//intermpu userslep si besoin
{
	int	t;

	t = get_timestamp_in_ms();
	while (1)
	{
		if ((get_timestamp_in_ms() - t) < time)
		{
			usleep(100);
		}
		else
			break ;
	}
}
