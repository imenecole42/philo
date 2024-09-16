/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:46:04 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/24 12:45:20 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->info->mutex_forks[philo->r_fork]));//fct biblio
		if (philo->philo_i % 2 == philo->info->fork_status[philo->r_fork])//utuliser que les paire a mangee
		{//si les pair ils finisent le statut cva incrementer
			print_status(philo, "has taken a fork");//
			if (philo->info->nb_philo == 1)
			{
				get_sleep(philo->info->time_to_die);
				pthread_mutex_unlock(&(philo->info
						->mutex_forks[philo->r_fork]));
			}
			break ;
		}
		pthread_mutex_unlock(&(philo->info->mutex_forks[philo->r_fork]));
		usleep(1000);//temp d'attente sur del
	}
}

void	take_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->info->mutex_forks[philo->l_fork]));
		if (philo->philo_i % 2 == philo->info->fork_status[philo->l_fork])
		{
			print_status(philo, "has taken a fork");
			break ;
		}
		pthread_mutex_unlock(&(philo->info->mutex_forks[philo->l_fork]));
		usleep(1000);
	}
}

void	take_two_forks(t_philo *philo)
{
	if (philo->philo_i % 2 == 0)
	{
		take_right_fork(philo);
		if (philo->info->nb_philo == 1)
			return ;
		take_left_fork(philo);
	}
	else if (philo->philo_i % 2 != 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
}

void	change_fork_status(t_philo *philo)
{
	if ((philo->info->nb_philo % 2 == 1)
		&& (philo->num == philo->info->nb_philo))
		philo->info->fork_status[philo->r_fork]
			= (philo->info->fork_status[philo->r_fork] + 1) & 1;//1 ou 0// sa depend statut c flag qui change
	else if ((philo->info->nb_philo % 2 == 1) && (philo->num == 1))
		philo->info->fork_status[philo->l_fork]
			= (philo->info->fork_status[philo->l_fork] + 1) & 1;
	else
	{
		philo->info->fork_status[philo->r_fork]
			= (philo->info->fork_status[philo->r_fork] + 1) & 1;
		philo->info->fork_status[philo->l_fork]
			= (philo->info->fork_status[philo->l_fork] + 1) & 1;
	}
	pthread_mutex_unlock(&(philo->info->mutex_forks[philo->r_fork]));
	pthread_mutex_unlock(&(philo->info->mutex_forks[philo->l_fork]));
}

void	philo_eat(t_philo *philo)
{
	take_two_forks(philo);
	if (philo->info->nb_philo == 1)
		return ;
	check_last_meal(philo);//calculer le moment de dernier repas
	print_status(philo, "is eating");
	get_sleep(philo->info->time_to_eat);//le temp de mager(exemple 200 temp donne dans arg)
	check_nbr_philo_eat(philo);//permettre de savoire le nbr de repas de chaque philo(pour 5 argument)
	change_fork_status(philo);//changer fork statur statut intitiliser a 0 apres c 1(flag)
	//mettre un cadena pour forchette
}
//le prmier et dernier change d'une facon et les autre sa marche pareille
//le 1er il change forchette de gauche et le dernier il change sa fourchette droite
//est les autres ils changes tout
//en cas de impaire le dernier il mange de la meme facon que les paire
//au moin il mange deux fois