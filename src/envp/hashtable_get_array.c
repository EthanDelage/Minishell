/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_get_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:17:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/14 17:17:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

static char	*elem_to_str(t_dict *elem)
{
	char			*str;
	const size_t	len_name = ft_strlen(elem->name);
	const size_t	len_value = ft_strlen(elem->value);

	str = (char *) malloc(sizeof(char) * (len_name + len_value + 2));
	if (errno)
		return (NULL);
	ft_strcpy(str, elem->name);
	str[len_name] = '=';
	ft_strcpy(&str[len_name + 1], elem->value);
	return (str);
}

static void	dict_to_array(char **array, t_dict *head, size_t *index)
{
	while (head != NULL)
	{
		array[*index] = elem_to_str(head);
		(*index)++;
		if (errno)
			return ;
		head = head->next;
	}
}

void	hashtable_array_clear(char **array)
{
	size_t	index;

	index = 0;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
}

char	**hashtable_get_array(t_hashtable *hashtable)
{
	size_t	index;
	char	**array;
	size_t	index_hashtable;

	array = (char **) ft_calloc(sizeof(char *), hashtable->nb_elem + 1);
	if (errno)
		return (NULL);
	index_hashtable = 0;
	index = 0;
	while (index_hashtable < hashtable->size)
	{
		dict_to_array(array, hashtable->dict[index_hashtable], &index);
		if (errno)
		{
			hashtable_array_clear(array);
			return (NULL);
		}
		index_hashtable++;
	}
	return (array);
}
