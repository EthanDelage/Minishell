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

static t_cmd_token	*cmd_token_new(int type, char *head, void *body);

void	cmd_token_add(t_cmd_token **cmd_stack, int type, char *head, void *body)
{
	t_cmd_token *new;

	new = cmd_token_new(type, head, body);
	if (new == NULL)
		return ;
	new->next = *cmd_stack;
	*cmd_stack = new;
}

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

void	cmd_token_add_cmd_arg(t_token *token, t_cmd_arg **arg_stack, size_t *i)
{
	size_t	last_i;
	int		current_type;

	line_trim_space(token->value, i);
	last_i = *i;
	while (token->value[*i] && !ft_isspace(token->value[*i]))
	{
		if (token->value[*i] == '"')
		{
			(*i)++;
			while (token->value[*i] && token->value[*i] != '"')
				(*i)++;
		}
		if (token->value[*i] == '\'')
		{
			(*i)++;
			while (token->value[*i] && token->value[*i] != '\'')
				(*i)++;
		}
		current_type = cmd_token_get_type(token->value + *i);
		if (current_type != COMMAND)
		{
			if (last_i != *i)
				cmd_arg_add(arg_stack,
				ft_substr(token->value, last_i, *i - last_i));
			cmd_token_add_redirect(token, current_type, i);
			return ;
		}
		(*i)++;
	}
	if (last_i != *i)
		cmd_arg_add(arg_stack,
					ft_substr(token->value, last_i, *i - last_i));
}

void	cmd_token_add_command(t_token *token, t_cmd_arg *cmd_arg_stack)
{
	cmd_token_add(&token->cmd_stack, COMMAND,
		  ft_strdup(cmd_arg_stack->arg), cmd_arg_stack_to_array(cmd_arg_stack));
}