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

t_cmd_token *cmd_lexer(t_token *token)
{
	size_t		i;
	t_cmd_token	*cmd_token;
	t_cmd_args	cmd_args;
	int			current_type;

	while (token->value[i])
	{
		current_type = cmd_token_get_type(token->value + i);
		if (current_type != COMMAND)
			cmd_token_add_redirect(token, current_type, &i);
		else
		{
			while ()
		}
	}
}