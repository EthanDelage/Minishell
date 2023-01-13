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

#include "line_lexer.h"

#include <stdio.h>

int	get_token_type(char *c)
{
	if (*c == '(')
		return (OPEN_PARENTHESIS);
	else if (*c == ')')
		return (CLOSE_PARENTHESIS);
	else if (*c == '&' && *(c + 1) == '&')
	{
		c++;
		return  (OPERATOR);
	}
	else if (*c == '|' && *(c + 1) == '|')
	{
		c++;
		return (OPERATOR);
	}
	else
		return (COMMAND);
}

void	add_command_token(t_line_token **token_stack, char *line, size_t *i)
{
	size_t last_i;

	last_i = *i;
	while (line[*i + 1] && get_token_type(line + *i + 1) == COMMAND)
	{
		if (line[(*i)] == '"')
		{
			(*i)++;
			while (line[*i] && line[*i] != '"')
				(*i)++;
		}
		if (line[(*i)] == '\'')
		{
			(*i)++;
			while (line[*i] && line[*i] != '\'')
				(*i)++;
		}
		(*i)++;
	}
	add_line_token(token_stack, COMMAND, ft_substr(line, last_i, *i - last_i + 1));
}

void add_parenthesis_token(t_line_token **token_stack, int type)
{
	if (type == OPEN_PARENTHESIS)
		add_line_token(token_stack, type, "(");
	else
		add_line_token(token_stack, type, ")");
}

void add_operator_token(t_line_token **token_stack, char *line, size_t *i)
{
	if (line[*i] == '&')
		add_line_token(token_stack, OPERATOR, "&&");
	else
		add_line_token(token_stack, OPERATOR, "||");
	(*i)++;
}

t_line_token *line_lexer(char *line)
{
	t_line_token	*token_stack;
	int				current_token;
	size_t			i;

	token_stack = NULL;
	i = 0;
	while (line[i])
	{
		current_token = get_token_type(line + i);
		if (current_token == COMMAND)
			add_command_token(&token_stack, line, &i);
		else if (current_token == OPEN_PARENTHESIS || current_token == CLOSE_PARENTHESIS)
			add_parenthesis_token(&token_stack, current_token);
		else
			add_operator_token(&token_stack, line, &i);
		i++;
	}
	if (errno)
	{
		//free
		return (NULL);
	}
	return (token_stack);
}