/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:08:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/16 21:08:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cmd_token.h"

int	cmd_token_get_type(const char *c)
{
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (APPEND_OUT);
		else
			return (REDIRECT_OUT);
	}
	else if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (HERE_DOC);
		else
			return (REDIRECT_IN);
	}
	else
		return (COMMAND);
}

void	cmd_token_reverse(t_cmd_token **head)
{
	t_cmd_token	*next;
	t_cmd_token	*curr;
	t_cmd_token	*prev;

	curr = *head;
	next = NULL;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}
