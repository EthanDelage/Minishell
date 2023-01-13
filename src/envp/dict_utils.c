/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:28:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/12 23:28:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

t_dict	*dict_new(char *name, char *value)
{
	t_dict	*new;

	new = (t_dict *) malloc(sizeof(t_dict));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	dict_add_back(t_dict **start, t_dict *new)
{
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	while ((*start)->next)
		*start = (*start)->next;
	(*start)->next = new;
}

t_dict	*remove_one(t_dict **node)
{
	t_dict	*next;

	if (node == NULL || *node == NULL)
		return (NULL);
	next = (*node)->next;
	free((*node)->name);
	free((*node)->value);
	free(*node);
	return (next);
}

void	clear_dict(t_dict **start)
{
	t_dict	*next;

	next = *start;
	while (next != NULL)
		next = remove_one(&next);
}
