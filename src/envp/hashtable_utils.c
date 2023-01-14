/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:58:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/13 18:58:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

t_dict	*hashtable_search(t_hashtable *hashtable, const char *name)
{
	size_t	key;
	t_dict	*elem;

	key = hashtable_get_key(name, hashtable->size);
	elem = hashtable->dict[key];
	while (elem != NULL && ft_strcmp(elem->name, name) != 0)
		elem = elem->next;
	return (elem);
}

size_t	hashtable_get_key(const char *name, size_t size)
{
	size_t	index;
	size_t	key;

	index = 0;
	key = 0;
	while (name[index])
	{
		key = key + (name[index] * 10 + index);
		index++;
	}
	return (key % size);
}

void	hashtable_push(t_hashtable *hashtable, t_dict *elem)
{
	t_dict	*head;
	size_t	key;

	key = hashtable_get_key(elem->name, hashtable->size);
	hashtable->nb_elem++;
	if (hashtable->dict[key] == NULL)
	{
		hashtable->dict[key] = elem;
		return ;
	}
	head = hashtable->dict[key];
	while (head->next != NULL)
		head = head->next;
	head->next = elem;
}

int	hashtable_remove_one(t_hashtable *hashtable, const char *name)
{
	size_t	key;
	t_dict	*head;

	key = hashtable_get_key(name, hashtable->size);
	if (hashtable->dict[key] == NULL)
		return (NOT_FOUND);
	head = hashtable->dict[key];
	if (ft_strcmp(name, head->name) == 0)
	{
		hashtable->dict[key] = head->next;
		dict_free_elem(&head);
		hashtable->nb_elem--;
		return (REMOVE);
	}
	while (head->next != NULL && ft_strcmp(name, head->next->name) != 0)
		head = head->next;
	if (head->next == NULL)
		return (NOT_FOUND);
	head->next = dict_free_elem(&head->next);
	hashtable->nb_elem--;
	return (REMOVE);
}
