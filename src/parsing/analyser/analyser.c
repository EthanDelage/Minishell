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
		if (token_iterator->type == COMMAND)
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
