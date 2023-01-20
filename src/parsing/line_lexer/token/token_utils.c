/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:51:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/16 17:51:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "line_lexer.h"

t_token	*token_new(int type, void *value)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->cmd_stack = NULL;
	token->next = NULL;
	return (token);
}

static int	is_operator(const char *c)
{
	return ((*c == '&' && *(c + 1) == '&') || (*c == '|' && *(c + 1) == '|'));
}

int	token_get_type(const char *c)
{
	if (is_operator(c))
		return (OPERATOR);
	else if (*c == '|')
		return (PIPE);
	else if (*c == '(')
		return (OPEN_PARENTHESIS);
	else if (*c == ')')
		return (CLOSE_PARENTHESIS);
	else
		return (COMMAND);
}

void	token_reverse(t_token **token_stack)
{
	t_token *next;
	t_token *curr;
	t_token *prev;

	curr = *token_stack;
	next = NULL;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*token_stack = prev;
}

void	line_trim_space(char *line, size_t *i)
{
	while (ft_strchr("\t\v\n\f\r ", line[*i]))
		(*i)++;
}
