/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:03:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/16 18:03:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "envp.h"

static t_list	*create_new_elem(int start, int end);

char	*replace(t_hashtable *envp_dict, char *line)
{
	char	*new_line;
	t_list	*head;

	head = NULL;
	return (new_line);
}

static t_list	*get_index(t_list *head, char *line)
{
	size_t	start;
	size_t	index;
	char	quote;
	t_list	*tmp;

	head = NULL;
	start = 0;
	index = 0;
	quote = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '$' && (quote == 0 || quote == '"'))
		{
			tmp = create_new_elem(start, index);
			if (errno)
			{
				ft_lstclear(head);
				return (NULL);
			}
			ft_lstadd_back(&head, tmp);
			while (line[index] != '\0' && !ft_isspace(line[index]))
				index++;
			start = index;
		}
		else if (line[index] == '"')
		{
			if (quote == 0)
				quote = line[index];
			else if (quote == '"')
				quote = 0;
		}
		index++;
	}
}

static t_list	*create_new_elem(int start, int end)
{
	t_list	*elem;
	int		*new;

	new = (int *) malloc(sizeof(int) * 2);
	if (errno)
	{
		free(elem);
		return (NULL);
	}
	new[0] = start;
	new[1] = end;
	elem = ft_lstnew(new);
	if (errno)
	{
		free(new);
		return (NULL);
	}
	return (elem);
}
