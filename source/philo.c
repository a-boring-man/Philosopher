/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:18:06 by jrinna            #+#    #+#             */
/*   Updated: 2023/07/17 13:13:00 by jrinna           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atol(char *s)
{
	long	i;
	int		signe;
	long	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((s[i] > 8 && s[i] < 14) || s[i] == 32)
		i++;
	while (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			signe = -signe;
	while ((s[i] >= '0' && s[i] <= '9'))
		result = result * 10 + (s[i++] - 48);
	return (result * signe);
}

static int	ft_rule_init(int ac, char **av, t_data *data)
{
	data->loop = -1;
	data->p_nbr = ft_atol(av[1]);
	if (!data->p_nbr)
		return (-1);
	data->t_die = ft_atol(av[2]);
	data->t_eat = ft_atol(av[3]);
	data->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->loop = ft_atol(av[5]);
	data->p = malloc(sizeof(t_philo) * data->p_nbr);
	if (!data->p)
		return (-1);
	data->dead = 0;
	pthread_mutex_init(&(data->death), NULL);
	return (0);
}

static void	ft_philo_init(t_data *data)
{
	int	nbr;

	nbr = data->p_nbr;
	gettimeofday(&(data->t_start), NULL);
	while (nbr-- > 0)
	{
		pthread_mutex_init(&(data->p[nbr].l_fork), NULL);
		data->p[nbr].p_id = nbr + 1;
		data->p[nbr].data = data;
		data->p[nbr].loop = 0;
		data->p[nbr].r_fork = &(data->p[(nbr + 1) % data->p_nbr].l_fork);
		gettimeofday(&(data->p[nbr].last_meal), NULL);
		pthread_create(&(data->p[nbr].t_id), NULL, ft_loop, &(data->p[nbr]));
	}
	ft_isdead(data);
	nbr = data->p_nbr;
	while (nbr-- > 0)
		pthread_join(data->p[nbr].t_id, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (0);
	if (ft_rule_init(ac, av, &data) == -1)
		return (0);
	ft_philo_init(&data);
	free(data.p);
}
