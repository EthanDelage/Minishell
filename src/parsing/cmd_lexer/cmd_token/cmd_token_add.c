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

static t_cmd_token	*cmd_token_new(int type, char *head, void *body)
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

void	cmd_token_add_redirect(t_token *token, int type, size_t *i)
{
	char *body;
	char *head;

	if (type == REDIRECT_OUT || type == REDIRECT_IN)
		(*i)++;
	else if (type == APPEND_OUT || type == HERE_DOC)
		*i += 2;
	body = cmd_token_get_redirect_body(token->value, i);
	head = cmd_token_get_redirect_head(type);
	cmd_token_add(&token->cmd_stack, type, head, body);
}

void	cmd_token_add_command(t_token *token, t_cmd_args *args_stack, size_t *i)
{
	size_t last_i;

	while (token->value[*i] && cmd_token_get_type(token->value + *i) == COMMAND)
	{
		while (ft_isspace())
	}
}