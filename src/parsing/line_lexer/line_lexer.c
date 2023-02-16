/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:14:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/13 16:14:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

#include <stdio.h>

static void	token_add_router(t_token **token_stack, t_type type,
				char *line, size_t *i);

/**
 * @brief Take a prompt line and return a t_token list representing the line.
 * @param line Usually a line form a terminal.
 * @return t_token list of command, operator, parenthesis and pipes.\n
 */
t_token	*line_lexer(char *line)
{
	t_token	*token_stack;
	t_type	type;
	size_t	i;

	if (line == NULL)
		return (NULL);
	token_stack = NULL;
	i = 0;
	while (line[i])
	{
		line_skip_space(line, &i);
		if (line[i])
		{
			type = token_get_type(line + i);
			token_add_router(&token_stack, type, line, &i);
			if (errno)
			{
				token_clear(token_stack);
				return (NULL);
			}
		}
	}
	token_reverse(&token_stack);
	return (token_stack);
}

static void	token_add_router(t_token **token_stack, t_type type,
								char *line, size_t *i)
{
	if (type == COMMAND)
		token_add_command(token_stack, line, i);
	else if (type == PIPE)
		token_add_pipe(token_stack, i);
	else if (type == OPEN_PARENTHESIS || type == CLOSE_PARENTHESIS)
		token_add_parenthesis(token_stack, type, i);
	else
		token_add_operator(token_stack, line, i);
}
