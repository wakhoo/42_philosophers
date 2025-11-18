/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:50:31 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 12:05:01 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	distory_all(char *str, t_cctv *cctv)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&cctv->common->write_lock);
	while (i < cctv->common->total_num)
	{
		pthread_mutex_destroy(&cctv->common->forks[i]);
		i++;
	}
}

void	create_philos(t_cctv *cctv)
{
	int			i;

	i = 0;
	if (pthread_create(&(cctv->observer), NULL, &checker, cctv) != 0)
		distory_all("Observer Thread create error", cctv);
	while (i < cctv->common->total_num)
	{
		if (pthread_create(&(cctv->philo[i]->brain),
				NULL, &routine, cctv->philo[i]) != 0)
			distory_all("Philo Thread create error", cctv);
		i++;
	}
	i = 0;
	while (i < cctv->common->total_num)
	{
		if (pthread_join(cctv->philo[i]->brain, NULL) != 0)
			distory_all("Philo Thread join error", cctv);
		i++;
	}
	if (pthread_join(cctv->observer, NULL) != 0)
		distory_all("Observer Thread join error", cctv);
}

void	start_philo(t_cctv *cctv)
{
	if (!cctv || !cctv->philo)
	{
		printf("Invalied pointer\n");
		return ;
	}
	create_philos(cctv);
	distory_all(NULL, cctv);
}

int	main(int argc, char **argv)
{
	t_cctv	*cctv;

	if (!(argc == 5 || argc == 6))
		error_exit("Wrong arguments");
	if (check_data(argc, argv))
		error_exit("Invalied input");
	cctv = NULL;
	init_set(argc, argv, &cctv);
	start_philo(cctv);
	tclear(TRUE);
	return (0);
}
