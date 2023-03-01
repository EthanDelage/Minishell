/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arg_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:31:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/22 23:31:00 by mururoah         ###   ########lyon.fr   */
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
