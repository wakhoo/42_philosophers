/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:17:38 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 13:09:36 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	is_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_hand);
		safe_print("has taken a fork", philo);
		pthread_mutex_lock(philo->left_hand);
	}
	else
	{
		pthread_mutex_lock(philo->left_hand);
		safe_print("has taken a fork", philo);
		pthread_mutex_lock(philo->right_hand);
	}
	safe_print("has taken a fork", philo);
	safe_print("is eating", philo);
	philo->last_eat = get_mstime();
	philo->ated_num++;
	usleep(philo->common->eat * 1000);
	pthread_mutex_unlock(philo->right_hand);
	pthread_mutex_unlock(philo->left_hand);
}

void	is_sleeping(t_philo *philo)
{
	safe_print("is sleeping", philo);
	usleep(philo->common->sleep * 1000);
}

void	is_thinking(t_philo *philo)
{
	safe_print("is thinking", philo);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->common->total_num == 1)
	{
		safe_print("has taken a fork", philo);
		usleep(philo->common->day_limit * 1000);
		safe_print("died", philo);
		philo->common->death_flag = TRUE;
		return (NULL);
	}
	while (philo->common->death_flag == FALSE)
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
		philo->current = get_mstime();
	}
	return (data);
}
