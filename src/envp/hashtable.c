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
	hashtable->dict = (t_dict **) ft_calloc(sizeof(t_dict *), size);
	if (errno)
	{
		free(hashtable);
		return (NULL);
	}
	hashtable->size = size;
	hashtable->nb_elem = 0;
	return (hashtable);
}

void	hashtable_clear(t_hashtable *hashtable)
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
