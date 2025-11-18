/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajeon <chajeon@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:19:52 by chajeon           #+#    #+#             */
/*   Updated: 2024/10/14 09:01:10 by chajeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	al_lstadd(t_bin **al_lst, t_bin *addnew)
{
	addnew->next = *al_lst;
	*al_lst = addnew;
}

int	al_lstdelone(t_bin **al_lst_head, t_bin *al_to_del)
{
	t_bin	*temp;
	t_bin	*next;
	t_bin	*prev;

	prev = *al_lst_head;
	temp = *al_lst_head;
	next = temp->next;
	while (temp)
	{
		if (temp == al_to_del)
		{
			if (temp == *al_lst_head)
				*al_lst_head = next;
			next = temp->next;
			prev->next = next;
			free(temp->ptr);
			free(temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	al_lstclear(t_bin **al_lst, int free_critical)
{
	t_bin	*temp;
	t_bin	*next;

	if (!*al_lst)
		return ;
	temp = *al_lst;
	while (temp)
	{
		next = temp->next;
		if ((temp->flag == TRUE && free_critical) || \
			temp->flag == FALSE)
			al_lstdelone(al_lst, temp);
		temp = next;
	}
}

t_bin	*al_lstnew(void *content, int critical)
{
	t_bin	*new;

	if (!content)
		return (NULL);
	new = (t_bin *)malloc(sizeof(t_bin));
	if (!new)
		return (NULL);
	new->ptr = content;
	new->flag = critical;
	new->next = NULL;
	return (new);
}
