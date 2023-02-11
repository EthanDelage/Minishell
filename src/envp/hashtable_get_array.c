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

static char	*elem_to_str(t_dict *elem);
static char	*elem_to_str_quote(t_dict *elem);
static void	dict_to_array(char **array, t_dict *head, size_t *index,
				bool quote);

/**
 * @brief Convert an hashtable into string array
 * @param quote: Boolean that determines whether values are enclosed in quotes
 */
char	**hashtable_get_array(t_hashtable *hashtable, bool quote)
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
		dict_to_array(array, hashtable->dict[index_hashtable], &index, quote);
		if (errno)
		{
			hashtable_array_clear(array);
			return (NULL);
		}
		index_hashtable++;
	}
	return (array);
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

/**
 * @brief Convert a part of the hashtable into string array
 * @param head: Part of the hashtable to convert
 * @param index: Start index to fill the string array
 * @param quote: Boolean that determines whether values are enclosed in quotes
 */
static void	dict_to_array(char **array, t_dict *head, size_t *index, bool quote)
{
	while (head != NULL)
	{
		if (quote == true)
			array[*index] = elem_to_str_quote(head);
		else
			array[*index] = elem_to_str(head);
		(*index)++;
		if (errno)
			return ;
		head = head->next;
	}
}

/**
 * @brief Convert an hashtable element to string without quote
 */
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

/**
 * @brief Convert an hashtable element to string with quote
 */
static char	*elem_to_str_quote(t_dict *elem)
{
	char			*str;
	const size_t	len_name = ft_strlen(elem->name);
	const size_t	len_value = ft_strlen(elem->value);

	str = (char *) malloc(sizeof(char) * (len_name + len_value + 4));
	if (errno)
		return (NULL);
	ft_strcpy(str, elem->name);
	str[len_name] = '=';
	str[len_name + 1] = '"';
	ft_strcpy(&str[len_name + 2], elem->value);
	str[len_name + len_value + 2] = '"';
	str[len_name + len_value + 3] = '\0';
	return (str);
}
