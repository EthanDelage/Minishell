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

/**
 * @brief
 * Initialize a cmd_stack token list in a command type t_token from the value field.\n
 * cmd_stack always start with the command if theres one and end with the redirects.\n
 * If an error occurred the stack is freed and errno is set.
 */
void	cmd_lexer(t_token *token)
{
	size_t		i;
	t_cmd_arg	*cmd_arg_stack;
	t_type		current_type;

	i = 0;
	cmd_arg_stack = NULL;
	while (token->value[i])
	{
		current_type = cmd_token_get_type(token->value + i);
		if (current_type != COMMAND)
			cmd_token_add_redirect(token, current_type, &i);
		else
			cmd_token_add_cmd_arg(token, &cmd_arg_stack, &i);
		if (errno)
		{
			cmd_token_clear(&token->cmd_stack);
			return ;
		}
	}
	cmd_token_reverse(&(token->cmd_stack));
	if (cmd_arg_stack != NULL)
		cmd_token_add_command(token, cmd_arg_stack);
}
