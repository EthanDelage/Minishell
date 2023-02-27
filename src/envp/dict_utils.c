/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:25:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/13 19:25:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

void	dict_free(t_dict **head)
{
	t_dict	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	while (tmp != NULL)
		tmp = dict_free_elem(tmp);
}

t_dict	*dict_free_elem(t_dict *elem)
{
	t_dict	*tmp;

	if (elem->name)
		free(elem->name);
	if (elem->value)
		free(elem->value);
	tmp = elem->next;
	free(elem);
	return (tmp);
}

void	dict_add_front(t_dict **head, t_dict *new_elem)
{
	if (head == NULL)
		return ;
	new_elem->next = *head;
	*head = new_elem;
}

void	dict_remove_one(t_dict **head, char *name)
{
	t_dict	*to_free;
	t_dict	*previous;
	t_dict	*current;

	if (*head == NULL)
		return ;
	if (ft_strcmp((*head)->name, name) == 0)
	{
		to_free = *head;
		*head = (*head)->next;
		dict_free_elem(to_free);
	}
	current = (*head)->next;
	previous = *head;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			previous->next = dict_free_elem(current);
		previous = current;
		current = current->next;
	}
}
