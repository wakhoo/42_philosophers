/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:46:27 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 12:05:07 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	error_exit_free(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	tclear(TRUE);
	exit(1);
}

void	alloc_error(void)
{
	ft_putstr_fd("Problem with allocation..XD\n", 2);
	tclear(TRUE);
	exit(1);
}
