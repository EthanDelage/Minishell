/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:58:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/13 18:58:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

t_hashtable	*hashtable_init(size_t size)
{
	t_hashtable	*hashtable;

	hashtable = (t_hashtable *) malloc(sizeof(t_hashtable));
	if (errno)
		return (NULL);
	hashtable->size = size;
	hashtable->dict	= (t_dict **) ft_calloc(sizeof(t_dict *), size);
	if (errno)
	{
		free(hashtable);
		return (NULL);
	}
	return (hashtable);
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

void	hashtable_clean(t_hashtable *hashtable)
{
	t_dict	*head_to_free;
	size_t	index;

	index = 0;
	while (index < hashtable->size)
	{
		head_to_free = hashtable->dict[index];
		if (head_to_free != NULL)
			dict_free(&head_to_free);
		index++;
	}
	free(hashtable->dict);
	free(hashtable);
}

//void	hashtable_remove_one(t_hashtable *hashtable, const char *name)
//{
//	size_t	key;
//	t_dict	**head;
//
//	key = hashtable_get_key(name, hashtable->size);
//	head = &hashtable->dict[key];
//}
