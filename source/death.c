/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:18:31 by jrinna            #+#    #+#             */
/*   Updated: 2023/07/17 13:16:34 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long long	ft_gettimestamp(t_philo *p)
{
	gettimeofday(&(p->data->t_cur), NULL);
	return ((u_int64_t)((p->data->t_cur.tv_usec - p->data->t_start.tv_usec)
		/ 1000) + (u_int64_t)((p->data->t_cur.tv_sec - p->data->t_start.tv_sec)
		* 1000));
}

int	ft_printf(t_philo *p, int id)
{
	pthread_mutex_lock(&(p->data->death));
	if (p->data->dead)
	{
		pthread_mutex_unlock(&(p->data->death));
		return (1);
	}
	if (id == FORK)
		printf("%llu %d has taken a fork\n",
			ft_gettimestamp(p), p->p_id);
	if (id == EATING)
	{
		printf("%llu %d is eating\n", ft_gettimestamp(p), p->p_id);
		gettimeofday(&(p->last_meal), NULL);
		if (p->loop > -1)
			p->loop++;
	}
	if (id == SLEEPING)
		printf("%llu %d is sleeping\n", ft_gettimestamp(p), p->p_id);
	if (id == THINKING)
		printf("%llu %d is thinking\n", ft_gettimestamp(p), p->p_id);
	pthread_mutex_unlock(&(p->data->death));
	return (0);
}

static int	ft_check_p_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->p_nbr)
	{
		gettimeofday(&(data->t_cur), NULL);
		if ((long)(data->t_cur.tv_sec * 1000 + data->t_cur.tv_usec / 1000
			- (data->p[i].last_meal.tv_sec * 1000
				+ data->p[i].last_meal.tv_usec / 1000)) > data->t_die)
		{
			printf("%llu %d died\n",
				ft_gettimestamp(&(data->p[i])), data->p[i].p_id);
			data->dead++;
			pthread_mutex_unlock(&(data->death));
			return (1);
		}
	}
	return (0);
}

static int	ft_no_more_loop(t_data *data)
{
	int	finish;
	int	i;

	i = -1;
	finish = 0;
	while (++i < data->p_nbr)
	{
		if (!finish && data->p[i].loop < data->loop)
			finish = 1;
	}
	return (!finish);
}

void	ft_isdead(t_data *data)
{
	while (1)
	{
		usleep(2000);
		pthread_mutex_lock(&(data->death));
		if (ft_check_p_death(data))
		{		
			pthread_mutex_unlock(&(data->death));
			break ;
		}
		if (data->loop != -1)
		{
			if (ft_no_more_loop(data))
			{
				data->dead++;
				pthread_mutex_unlock(&(data->death));
				break ;
			}
		}
		pthread_mutex_unlock(&(data->death));
	}
}
