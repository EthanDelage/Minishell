/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:47:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/30 22:47:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

int	cmd_arg_remove_quote(t_cmd_arg *head)
{
	while (head)
	{
		head->arg = trim_quotes(head->arg);
		if (errno)
			return (FAILURE);
		head = head->next;
	}
	return (SUCCESS);
}

/**
 * @brief Split the arguments after replacing the environment variables
 */
t_cmd_arg	*split_arg(t_cmd_arg *current)
{
	size_t	start;
	size_t	index;
	size_t	nb_args;
	char	*arg;

	arg = current->arg;
	start = 0;
	line_skip_isspace(arg, &start);
	index = start;
	get_end_index(arg, &index);
	if (arg[index] == '\0' && start == 0)
		return (current->next);
	current->arg = ft_substr(arg, start, index - start);
	nb_args = 1;
	line_skip_isspace(arg, &index);
	while (arg[index])
	{
		add_new_arg(arg, &index, current);
		line_skip_isspace(arg, &index);
		nb_args++;
	}
	return (get_return_cmd_arg(current, nb_args));
}

void	remove_void_arg(t_cmd_arg **head)
{
	t_cmd_arg	*current;
	t_cmd_arg	*previous;

	if (*head == NULL)
		return ;
	previous = *head;
	current = (*head)->next;
	while (current)
	{
		if (current->arg[0] == '\0')
		{
			previous->next = current->next;
			cmd_arg_clear_node(current);
			current = previous->next;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	current = *head;
	if (current->arg[0] == '\0')
	{
		(*head) = current->next;
		cmd_arg_clear_node(current);
	}
}
