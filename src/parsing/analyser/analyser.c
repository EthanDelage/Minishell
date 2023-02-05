/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:26:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/25 14:26:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

static int	cmd_analyser(t_token *token);
static int	verify_only_redirection(t_token *redirect_token);
static char	*last_cmd_arg(t_cmd_arg *cmd_arg_stack);

t_token	*analyser(char *line)
{
	t_token	*token_stack;
	t_token	*token_iterator;

	token_stack = line_lexer(line);
	if (line_parser(token_stack) == FAILURE)
	{
		token_clear(&token_stack);
		return (NULL);
	}
	token_iterator = token_stack;
	while (token_iterator)
	{
		if (token_iterator->type == CLOSE_PARENTHESIS
			&& token_iterator->next && token_iterator->next->type == COMMAND)
		{
			if (verify_only_redirection(token_iterator->next) == FAILURE)
			{
				token_clear(&token_stack);
				return (NULL);
			}
			token_iterator = token_iterator->next;
		}
		else if (token_iterator->type == COMMAND)
		{
			if (cmd_analyser(token_iterator) == FAILURE)
			{
				token_clear(&token_stack);
				return (NULL);
			}
		}
		token_iterator = token_iterator->next;
	}
	return (token_stack);
}

static int	cmd_analyser(t_token *token)
{
	cmd_lexer(token);
	if (errno)
		return (FAILURE);
	if (cmd_parser(token) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	verify_only_redirection(t_token *redirect_token)
{
	if (cmd_analyser(redirect_token) == FAILURE)
		return (FAILURE);
	if (redirect_token->cmd_stack->type == COMMAND)
	{
		return (error_syntax(last_cmd_arg(
					(t_cmd_arg *) redirect_token->cmd_stack->body)));
	}
	return (SUCCESS);
}

static char	*last_cmd_arg(t_cmd_arg *cmd_arg_stack)
{
	if (cmd_arg_stack == NULL)
		return (NULL);
	if (cmd_arg_stack->next == NULL)
		return (cmd_arg_stack->arg);
	while (cmd_arg_stack->next)
		cmd_arg_stack = cmd_arg_stack->next;
	return (cmd_arg_stack->arg);
}
