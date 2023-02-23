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
#include "analyser.h"

static int		cmd_analyser(t_token *token);
static t_token	*token_analyser(t_token *token);
static int		analyse_subshell_redirect(t_token *redirect_token);
static char		*get_last_cmd_arg(t_cmd_arg *cmd_arg_stack);

/**
 * @brief Lex and parse line parameter.
 * @return Return a t_token stack representing the line.
 * Return NULL if an error occurred.
 */
t_token	*analyser(char *line)
{
	t_token	*token_stack;
	t_token	*token_iterator;

	token_stack = line_lexer(line);
	if (token_stack == NULL)
		return (NULL);
	if (line_parser(token_stack) == FAILURE)
	{
		token_clear(token_stack);
		return (NULL);
	}
	token_iterator = token_stack;
	while (token_iterator)
	{
		token_iterator = token_analyser(token_iterator);
		if (token_iterator == NULL)
		{
			token_clear(token_stack);
			return (NULL);
		}
		token_iterator = token_iterator->next;
	}
	return (token_stack);
}

/**
 * @brief Lex and parse a line to a token_stack
 * @return
 * Return NULL if an error occurred or if the line doesn't have a good syntax.
 * Return the head of the token_stack otherwise.
 */
static t_token	*token_analyser(t_token *token)
{
	if (token->type == CLOSE_PARENTHESIS
		&& token->next && token->next->type == COMMAND)
	{
		if (analyse_subshell_redirect(token->next) == FAILURE)
			return (NULL);
		token = token->next;
	}
	else if (token->type == COMMAND)
		if (cmd_analyser(token) == FAILURE)
			return (NULL);
	return (token);
}

/**
 * @brief Lex and parse a command t_token
 * @return
 * Return FAILURE	if an error occurred or if cmd_token is not a redirection.
 * Return SUCCESS otherwise.
 */
static int	cmd_analyser(t_token *token)
{
	cmd_lexer(token);
	if (errno)
		return (FAILURE);
	if (cmd_parser(token) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Lex and parse the token next to a closed parenthesis.
 * @return
 * Return FAILURE	if an error occurred or if cmd_token is not a redirection.
 * Return SUCCESS otherwise.
 */
static int	analyse_subshell_redirect(t_token *redirect_token)
{
	t_cmd_arg	*cmd_arg_stack;

	if (cmd_analyser(redirect_token) == FAILURE)
		return (FAILURE);
	if (redirect_token->cmd_stack->type == COMMAND)
	{
		cmd_arg_stack = (t_cmd_arg *) redirect_token->cmd_stack->body;
		return (error_syntax(get_last_cmd_arg(cmd_arg_stack)));
	}
	return (SUCCESS);
}

static char	*get_last_cmd_arg(t_cmd_arg *cmd_arg_stack)
{
	if (cmd_arg_stack == NULL)
		return (NULL);
	if (cmd_arg_stack->next == NULL)
		return (cmd_arg_stack->arg);
	while (cmd_arg_stack->next)
		cmd_arg_stack = cmd_arg_stack->next;
	return (cmd_arg_stack->arg);
}
