/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:05:25 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/23 12:05:27 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	unlink_alloc(t_bin **bins, void *ptr)
{
	t_bin	*temp;
	t_bin	*prev;

	prev = NULL;
	if (!*bins)
		return ;
	temp = *bins;
	while (temp)
	{
		if (ptr == temp->ptr)
		{
			if (temp->next && prev)
				prev->next = temp->next;
			else
				*bins = temp->next;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

static void	*new_alloc(t_bin **bins, int size, int critical)
{
	void	*new_malloc;
	t_bin	*lst_bins;

	new_malloc = malloc(size);
	if (!new_malloc)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (NULL);
	}
	lst_bins = al_lstnew(new_malloc, critical);
	if (!lst_bins)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		free(new_malloc);
		return (NULL);
	}
	al_lstadd(bins, lst_bins);
	return (new_malloc);
}

static void	free_alloc(t_bin **bins, void *ptr)
{
	t_bin	*temp;
	t_bin	*next;

	if (!*bins)
		return ;
	temp = *bins;
	while (temp)
	{
		next = temp->next;
		if (ptr == temp->ptr)
		{
			al_lstdelone(bins, temp);
			temp = next;
			return ;
		}
		temp = next;
	}
}

void	*ft_allocator(int size, t_alloc_code code, void *ptr, int critical)
{
	static t_bin	*lst_bins;

	if (code == ALLOC)
		return (new_alloc(&lst_bins, size, critical));
	else if (code == CLEAR)
		al_lstclear(&lst_bins, critical);
	else if (code == FREE)
		free_alloc(&lst_bins, ptr);
	else if (code == UNLINK)
		unlink_alloc(&lst_bins, ptr);
	return (NULL);
}
