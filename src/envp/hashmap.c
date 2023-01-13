/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:21:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/12 23:21:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

size_t	get_key(char *name)
{
	size_t	sum;

	sum = 0;
	while (*name)
	{
		sum += (unsigned char) *name;
		name++;
	}
	return (sum % SIZE_HASHMAP);
}

void	hash_elem(t_dict **list, t_dict *new)
{
	t_dict	*tmp;
	size_t	key;

	key = get_key(new->name);
	if (list[key] == NULL)
	{
		list[key] = new;
		return ;
	}
	tmp = list[key];
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_dict	**init_hashmap(void)
{
	t_dict	**hashmap;

	hashmap = (t_dict **) ft_calloc(sizeof(t_dict *), SIZE_HASHMAP);
	return (hashmap);
}

static void	display_list(t_dict *start)
{
	while (start)
	{
		printf("\tName:\t\t%s\n", start->name);
		printf("\tValue:\t\t%s\n\n", start->value);
		start = start->next;
	}
}

void	display_hashmap(t_dict **hashmap)
{
	size_t	index;

	index = 0;
	while (index < SIZE_HASHMAP)
	{
		printf("Index: %zu\n\n", index);
		display_list(hashmap[index]);
		index++;
	}
}
