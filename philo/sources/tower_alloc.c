/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tower_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:18:46 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 11:59:19 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*tlloc(int size, int flag)
{
	return (ft_allocator(size, ALLOC, NULL, flag));
}

void	tclear(int flag)
{
	if (flag)
		ft_allocator(0, CLEAR, NULL, TRUE);
	else
		ft_allocator(0, CLEAR, NULL, FALSE);
}

void	tfree(void *ptr)
{
	ft_allocator(0, FREE, ptr, 0);
}

void	tunlink(void *ptr)
{
	ft_allocator(0, UNLINK, ptr, 0);
}
