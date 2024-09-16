/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdukuray <gdukuray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:38:34 by gdukuray          #+#    #+#             */
/*   Updated: 2023/02/17 11:59:09 by gdukuray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				num;
	int				philo_i;
	pthread_t		philo_id;
	int				numb_times_ate;
	int				r_fork;
	int				l_fork;
	int				t_last_meal;
}					t_philo;

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				fork_status[250];
	int				one_philo_has_finish;
	int				start;
	int				end;
	int				die;
	int				nb_times_must_eat;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_forks[250];
	pthread_mutex_t	mutex_writing;
	t_philo			philo[250];
}					t_info;

/*
** ----- main.c -----
*/
void				error_args(void);
int					ft_create_philo(t_info *info);

/*
** ----- init.c -----
*/
int					init_all(t_info *info, char **av);
void				ft_init_info(t_info *info, char **av);
int					*init_philo(t_info *info);
int					init_mutex_die(t_info *info);
int					init_mutex_end(t_info *info);
int					init_mutex_writing(t_info *info);
int					init_mutex_forks(t_info *info);

/*
** ----- utils.c -----
*/

long				ft_atoi(char *nptr);
int					get_timestamp_in_ms(void);
void				print_status(t_philo *philo, char *str);
void				print_status_die(t_philo *philo, char *str);
void				get_sleep(int time);
int					check_mutex_end(t_info *info);
int					check_mutex_die(t_info *info);
int					check_mutex_eat(t_info *info, t_philo *philo);
int					check_mutex_last_meal(t_philo *philo);
int					set_die(t_info *info);

/*
** ----- philo.c and philo_eat.c-----
*/
void				*philo_routine(void *arg);
void				philo_eat(t_philo *philo);
void				check_nbr_philo_eat(t_philo *philo);
void				check_last_meal(t_philo *philo);

/*
** ----- die_or_end.c -----
*/

void				check_if_philo_is_dead(t_info *info);
int					end_philo(t_info *info);
int					is_death(t_info *info);
int					is_end(t_info *info);

#endif