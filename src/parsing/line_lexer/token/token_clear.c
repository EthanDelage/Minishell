/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:10:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/14 17:10:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"

static void	token_free_elem(t_token *elem)
{
	if (elem->type == COMMAND)
		free(elem->value);
	free(elem);
}

void	token_clear(t_token **token_stack)
{
	t_token	*next;

	while (*token_stack)
	{
		next = (*token_stack)->next;
		token_free_elem(*token_stack);
		*token_stack = next;
	}
}
