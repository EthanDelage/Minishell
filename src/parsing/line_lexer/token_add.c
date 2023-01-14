/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:50:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/13 17:50:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "line_lexer.h"

static t_line_token	*token_new(int type, void *value)
{
	t_line_token	*token;

	token = (t_line_token *) malloc(sizeof(t_line_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

static void	token_add(t_line_token **stack, int type, void *value)
{
	t_line_token	*new;

	new = token_new(type, value);
	if (new == NULL)
		return ;
	new->next = *stack;
	*stack = new;
}

void	token_add_command(t_line_token **token_stack, char *line, size_t *i)
{
	size_t	last_i;

	last_i = *i;
	while (line[*i] && token_get_type(line + *i) == COMMAND)
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
	token_add(token_stack, COMMAND,
		ft_substr(line, last_i, *i - last_i));
}

void	token_add_parenthesis(t_line_token **token_stack, int type, size_t *i)
{
	if (type == OPEN_PARENTHESIS)
		token_add(token_stack, type, "(");
	else
		token_add(token_stack, type, ")");
	(*i)++;
}

void	token_add_operator(t_line_token **token_stack, const char *line,
			size_t *i)
{
	if (line[*i] == '&')
		token_add(token_stack, OPERATOR, "&&");
	else
		token_add(token_stack, OPERATOR, "||");
	(*i) += 2;
}
