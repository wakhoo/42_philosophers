/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:27:39 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 12:02:19 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	min;

	i = 0;
	res = 0;
	min = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		if (i > 0)
		{
			if (str[i - 1] == '-')
				min = min * (-1);
		}
		res = res * 10 + (str[i++] - '0');
	}
	return (res * min);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
