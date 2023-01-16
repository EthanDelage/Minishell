/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:23:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/16 21:23:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cmd_token.h"

t_cmd_token	*cmd_token_new(int type, char *head, void *body)
{
	t_cmd_token	*cmd_token;

	cmd_token = malloc(sizeof(t_cmd_token));
	if (cmd_token == NULL)
		return (NULL);
	cmd_token->type = type;
	cmd_token->head = head;
	cmd_token->body = body;
	cmd_token->next = NULL;
	return (cmd_token);
}

void	cmd_token_add(t_cmd_token **cmd_stack, int type, char *head, void *body)
{
	t_cmd_token *new;

	new = cmd_token_new(type, head, body);
	if (new == NULL)
		return ;
	new->next = *cmd_stack;
	*cmd_stack = new;
}

void	cmd_token_add_redirect(t_cmd_token **cmd_stack, int type, int *i)
{
	if (type == REDIRECT_OUT)

}