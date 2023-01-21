/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:48:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/17 15:48:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cmd_token.h"

static	t_cmd_arg	*cmd_arg_new(char *arg);

void	cmd_arg_add(t_cmd_arg **cmd_arg_stack, char *arg)
{
	t_cmd_arg	*new;

	new = cmd_arg_new(arg);
	if (new == NULL)
		return ;
	new->next = *cmd_arg_stack;
	*cmd_arg_stack = new;
}

static	t_cmd_arg	*cmd_arg_new(char *arg)
{
	t_cmd_arg	*cmd_arg;

	cmd_arg = malloc(sizeof (t_cmd_arg));
	if (cmd_arg == NULL)
		return (NULL);
	cmd_arg->arg = arg;
	cmd_arg->next = NULL;
	return (cmd_arg);
}

void	cmd_arg_reverse(t_cmd_arg **cmd_arg)
{
	t_cmd_arg	*next;
	t_cmd_arg	*curr;
	t_cmd_arg	*prev;

	curr = *cmd_arg;
	next = NULL;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*cmd_arg = prev;
}

int	cmd_arg_size(t_cmd_arg *cmd_arg_stack)
{
	t_cmd_arg	*iterator;
	int			count;

	count = 0;
	iterator = cmd_arg_stack;
	while (iterator)
	{
		count++;
		iterator = iterator->next;
	}
	return (count);
}

char	**cmd_arg_stack_to_array(t_cmd_arg *cmd_arg_stack)
{
	char		**args;
	t_cmd_arg	*iterator;
	int			i;

	args = malloc((cmd_arg_size(cmd_arg_stack) + 1) * sizeof (*cmd_arg_stack));
	i = 0;
	iterator = cmd_arg_stack;
	while (iterator)
	{
		args[i] = ft_strdup(iterator->arg);
		i++;
		iterator = iterator->next;
	}
	args[i] = NULL;
	return (args);
}
