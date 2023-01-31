/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:49:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/31 00:49:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"
#include "token.h"

static t_cmd_arg	*create_new_node(char *value, t_cmd_arg *next);

void	line_skip_isspace(char *line, size_t *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

void	get_end_index(char *arg, size_t *index)
{
	while (arg[*index] && !ft_isspace(arg[*index]))
	{
		if (arg[*index] == '"' || arg[*index] == '\'')
			line_skip_quote(arg, index);
		else
			(*index)++;
	}
}

int	add_new_arg(char *arg, size_t *index, t_cmd_arg *current)
{
	t_cmd_arg	*new_node;
	char		*new_arg;
	size_t		start;

	start = *index;
	get_end_index(arg, index);
	new_arg = ft_substr(arg, start, *index - start);
	if (errno)
		return (EXIT_FAILURE);
	new_node = create_new_node(current->arg, current->next);
	if (errno)
		return (EXIT_FAILURE);
	current->next = new_node;
	current->arg = new_arg;
	return (EXIT_SUCCESS);
}

static t_cmd_arg	*create_new_node(char *value, t_cmd_arg *next)
{
	t_cmd_arg	*new;

	new = (t_cmd_arg *) malloc(sizeof(t_cmd_arg));
	if (errno)
		return (NULL);
	new->arg = value;
	new->next = next;
	return (new);
}

t_cmd_arg	*get_return_cmd_arg(t_cmd_arg *current, size_t nb_new_arg)
{
	while (current && nb_new_arg)
	{
		nb_new_arg--;
		current = current->next;
	}
	return (current);
}
