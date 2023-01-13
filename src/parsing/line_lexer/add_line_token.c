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

t_line_token	*new_line_token(int type, void *value)
{
	t_line_token *token;

	token = malloc(sizeof(t_line_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_line_token(t_line_token **stack, int type, void *value)
{
	t_line_token *new;

	new = new_line_token(type, value);
	if (new == NULL)
		return ;
	new->next = *stack;
	*stack = new;
}