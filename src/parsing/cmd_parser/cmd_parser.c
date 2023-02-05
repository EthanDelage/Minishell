/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:04:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/20 04:04:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

int	cmd_parser(t_token *head)
{
	t_cmd_token	*cmd_token;

	cmd_token = head->cmd_stack;
	while (cmd_token != NULL)
	{
		if (cmd_token->type != COMMAND
			&& ((t_redirect_param *) cmd_token->body)->body[0] == '\0')
		{
			if (cmd_token->next != NULL)
				return (error_syntax(cmd_token->next->head));
			else if (head->next)
				return (error_syntax(head->next->value));
			else
				return (error_syntax("newline"));
		}
		cmd_token = cmd_token->next;
	}
	return (SUCCESS);
}
