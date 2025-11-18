/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:49:46 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 13:03:02 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	hold_forks(t_cctv *cctv)
{
	int	i;
	int	total;

	i = 0;
	total = cctv->common->total_num;
	while (i < cctv->common->total_num)
	{
		pthread_mutex_init(&cctv->common->forks[i], NULL);
		cctv->philo[i]->right_hand = &cctv->common->forks[i];
		if (i != 0)
			cctv->philo[i]->left_hand = &cctv->common->forks[i - 1];
		else
			cctv->philo[i]->left_hand = &cctv->common->forks[total - 1];
		i++;
	}
}

t_philo	**init_philo(char **argv, t_cctv *cctv)
{
	t_philo	**philos;
	int		i;

	(void)argv;
	philos = tlloc(sizeof(t_philo *) * cctv->common->total_num, 1);
	if (!philos)
		alloc_error();
	i = 0;
	while (i < cctv->common->total_num)
	{
		philos[i] = tlloc(sizeof(t_philo), 1);
		if (!philos[i])
			alloc_error();
		philos[i]->id = i + 1;
		philos[i]->last_eat = 0;
		philos[i]->current = 0;
		philos[i]->common = cctv->common;
		philos[i]->ated_num = 0;
		philos[i]->enough_eat = FALSE;
		i++;
	}
	return (philos);
}

t_common	*init_common(int argc, char **argv)
{
	t_common	*common;

	common = tlloc(sizeof(t_common), 1);
	if (!common)
		alloc_error();
	common->total_num = ft_atoi(argv[1]);
	if (common->total_num <= 0)
		error_exit_free("Not good input");
	common->day_limit = ft_atoi(argv[2]);
	common->eat = ft_atoi(argv[3]);
	common->sleep = ft_atoi(argv[4]);
	common->start_day = get_mstime();
	if (common->day_limit <= 0 || common->eat <= 0 || common->sleep <= 0)
		error_exit_free("Not good input");
	common->have_to_eat = -1;
	if (argc == 6)
		common->have_to_eat = ft_atoi(argv[5]);
	common->num_ate_philos = 0;
	common->death_flag = FALSE;
	common->forks = tlloc((sizeof(pthread_mutex_t) * common->total_num), 1);
	if (!common->forks)
		alloc_error();
	pthread_mutex_init(&common->write_lock, NULL);
	return (common);
}

void	init_set(int argc, char **argv, t_cctv **cctv)
{
	*cctv = tlloc(sizeof(t_cctv), 1);
	if (!*cctv)
		alloc_error();
	(*cctv)->common = init_common(argc, argv);
	(*cctv)->philo = init_philo(argv, *cctv);
	hold_forks(*cctv);
}
