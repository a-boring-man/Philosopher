/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:18:44 by jrinna            #+#    #+#             */
/*   Updated: 2022/03/18 15:05:15 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>

# define EATING 0
# define FORK 1
# define SLEEPING 2
# define THINKING 3

typedef struct s_philo
{
	int				loop;
	int				p_id;
	struct s_data	*data;
	struct timeval	last_meal;
	pthread_t		t_id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	int				dead;
	long			loop;
	long			p_nbr;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	struct timeval	t_cur;
	struct timeval	t_start;
	pthread_mutex_t	death;
	t_philo			*p;
}	t_data;

int		ft_printf(t_philo *p, int id);
void	ft_isdead(t_data *data);
void	*ft_loop(void *arg);

#endif