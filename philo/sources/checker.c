/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:15:41 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 13:09:32 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_data(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_digit(argv[i]))
			return (1);
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

void	safe_print(char *str, t_philo *philo)
{
	size_t	start_time;

	start_time = philo->common->start_day;
	pthread_mutex_lock(&philo->common->write_lock);
	if (philo->common->death_flag == FALSE)
		printf("%zu %d %s\n", get_mstime() - start_time, philo->id, str);
	pthread_mutex_unlock(&philo->common->write_lock);
}

void	set_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->common->write_lock);
	philo->common->death_flag = TRUE;
	pthread_mutex_unlock(&philo->common->write_lock);
}

int	check_death(t_philo *philo)
{
	if (philo->common->num_ate_philos == philo->common->total_num)
	{
		set_death_flag(philo);
		return (TRUE);
	}
	if (philo->last_eat != 0 && philo->current != 0
		&& philo->current > philo->common->day_limit + philo->last_eat)
	{
		safe_print("died", philo);
		set_death_flag(philo);
		return (TRUE);
	}
	if (philo->common->have_to_eat > 0 && philo->enough_eat == FALSE
		&& philo->ated_num >= philo->common->have_to_eat)
	{
		pthread_mutex_lock(&philo->common->write_lock);
		philo->enough_eat = TRUE;
		philo->common->num_ate_philos++;
		pthread_mutex_unlock(&philo->common->write_lock);
	}
	return (FALSE);
}

void	*checker(void *data)
{
	t_cctv	*cctv;
	int		i;

	cctv = (t_cctv *)data;
	while (1)
	{
		if (cctv->common->death_flag == TRUE)
			break ;
		i = 0;
		while (i < cctv->common->total_num)
		{
			if (check_death(cctv->philo[i]))
			{
				cctv->common->death_flag = TRUE;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
