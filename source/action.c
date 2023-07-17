/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:04:28 by jrinna            #+#    #+#             */
/*   Updated: 2022/03/18 14:53:37 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_mutex_unlock(t_philo *p)
{
	pthread_mutex_unlock(&(p->l_fork));
	pthread_mutex_unlock(p->r_fork);
}

static int	ft_mutex_lock(t_philo *p)
{
	if (p->r_fork == &(p->l_fork))
	{
		pthread_mutex_lock(&(p->l_fork));
		ft_printf(p, FORK);
		return (1);
	}
	if (!(p->p_id % 2))
	{
		pthread_mutex_lock(&(p->l_fork));
		ft_printf(p, FORK);
		pthread_mutex_lock(p->r_fork);
		ft_printf(p, FORK);
	}
	else
	{
		pthread_mutex_lock(p->r_fork);
		ft_printf(p, FORK);
		pthread_mutex_lock(&(p->l_fork));
		ft_printf(p, FORK);
	}
	return (0);
}

static void	ft_msleep(t_philo *p, long timems)
{
	struct timeval	t_us;
	struct timeval	t_uf;

	gettimeofday(&(t_us), NULL);
	usleep(0.5 * timems * 1000);
	gettimeofday(&(t_uf), NULL);
	while ((long)((t_uf.tv_usec - t_us.tv_usec) / 1000
		+ (t_uf.tv_sec - t_us.tv_sec) * 1000) < timems)
	{
		if (p->data->p_nbr > 90)
			usleep(600);
		else
			usleep(100);
		gettimeofday(&(t_uf), NULL);
	}
}

void	*ft_loop(void *arg)
{
	t_philo	*p;
	int		i;

	p = arg;
	i = 0;
	if (!(p->p_id % 2))
		ft_msleep(p, p->data->t_eat * 0.9);
	while (!i)
	{
		if (ft_mutex_lock(p))
			break ;
		i += ft_printf(p, EATING);
		gettimeofday(&(p->last_meal), NULL);
		ft_msleep(p, p->data->t_eat);
		ft_mutex_unlock(p);
		if (i == 2)
			ft_msleep(p, p->data->t_die);
		if (i == 2)
			break ;
		i += ft_printf(p, SLEEPING);
		ft_msleep(p, p->data->t_sleep);
		i += ft_printf(p, THINKING);
		ft_msleep(p, 1);
	}
	return (0);
}
