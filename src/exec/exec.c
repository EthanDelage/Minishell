/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/24 16:43:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

extern unsigned char	g_return_value;

static t_token	*exec_get_next_token(t_token *token);
static t_token	*exec_get_next_operator(t_token *token);

t_token	*exec_operator(t_token *head, t_hashtable *envp_dict)
{
	head = exec_router(head, envp_dict);
	while (head && head->type == OPERATOR)
	{
		if ((*head->value == '&' && g_return_value == 0)
			|| (*head->value == '|' && g_return_value != 0))
			head = exec_router(head->next, envp_dict);
		else
			head = exec_get_next_operator(head->next);
	}
	return (head);
}

t_token	*exec_router(t_token *head, t_hashtable *envp_dict)
{
	if (head->next && head->next->type == PIPE)
	{
		exec_pipe(head, envp_dict, STDIN_FILENO);
		return (exec_get_next_token(head));
	}
	else
	{
		exec_cmd(head, envp_dict);
		return (head->next);
	}
}

static t_token	*exec_get_next_token(t_token *token)
{
	while (token)
	{
		if (token->next == NULL || token->next->type == OPERATOR)
			return (token->next);
		token = token->next;
	}
	return (token);
}

static t_token	*exec_get_next_operator(t_token *token)
{
	while (token && token->type != OPERATOR)
	{
		if (token->type == OPEN_PARENTHESIS || token->type == CLOSE_PARENTHESIS)
			return (token);
		token = token->next;
	}
	return (token);
}
