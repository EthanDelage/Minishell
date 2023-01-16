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

static void	line_trim_space(char *line, size_t *i)
{
	while (ft_strchr("\t\v\n\f\r ", line[*i]))
		(*i)++;
}

t_token	*line_lexer(char *line)
{
	t_token	*token_stack;
	int				token;
	size_t			i;

	token_stack = NULL;
	i = 0;
	while (line[i])
	{
		line_trim_space(line, &i);
		token = token_get_type(line + i);
		if (token == COMMAND)
			token_add_command(&token_stack, line, &i);
		else if (token == PIPE)
			token_add_pipe(&token_stack, &i);
		else if (token == OPEN_PARENTHESIS || token == CLOSE_PARENTHESIS)
			token_add_parenthesis(&token_stack, token, &i);
		else
			token_add_operator(&token_stack, line, &i);
		if (errno)
		{
			token_clear(&token_stack);
			return (NULL);
		}
	}
	return (token_stack);
}
