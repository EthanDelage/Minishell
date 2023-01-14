/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:09:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/14 17:09:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

static void	hashtable_display_dict(t_dict *dict);

void	hashtable_display(t_hashtable *hashtable)
{
	size_t	index;

	index = 0;
	while (index < hashtable->size)
	{
		printf("Index: %zu\n", index);
		hashtable_display_dict(hashtable->dict[index]);
		printf("\n");
		index++;
	}
}

static void	hashtable_display_dict(t_dict *dict)
{
	while (dict != NULL)
	{
		printf("\tName:\t%s\n", dict->name);
		printf("\tValue:\t%s\n\n", dict->value);
		dict = dict->next;
	}
}
