/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:43:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/16 19:43:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cmd_token.h"

void	cmd_lexer(t_token *token)
{
	size_t		i;
	t_cmd_arg	*cmd_arg_stack;
	int			current_type;

	i = 0;
	cmd_arg_stack = NULL;
	while (token->value[i])
	{
		current_type = cmd_token_get_type(token->value + i);
		if (current_type != COMMAND)
			cmd_token_add_redirect(token, current_type, &i);
		else
			cmd_token_add_cmd_arg(token, &cmd_arg_stack, &i);
	}
	cmd_token_reverse(&(token->cmd_stack));
	if (cmd_arg_stack != NULL)
	{
		cmd_arg_reverse(&cmd_arg_stack);
		cmd_token_add_command(token, cmd_arg_stack);
	}
}
