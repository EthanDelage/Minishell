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

static t_cmd_token	*cmd_token_new(t_type type, char *head, void *body);

void	cmd_token_add(t_cmd_token **stack, t_type type, char *head, void *body)
{
	t_cmd_token	*new;

	new = cmd_token_new(type, head, body);
	if (new == NULL)
		return ;
	new->next = *stack;
	*stack = new;
}

static t_cmd_token	*cmd_token_new(t_type type, char *head, void *body)
{
	t_cmd_token	*cmd_token;

	cmd_token = malloc(sizeof(t_cmd_token));
	if (cmd_token == NULL)
		return (NULL);
	cmd_token->type = type;
	cmd_token->head = head;
	cmd_token->body_type = STACK;
	cmd_token->body = body;
	cmd_token->next = NULL;
	return (cmd_token);
}

/**
 * @brief
 * Add a redirect type token from token's value field to the cmd_token stack.
 */
void	cmd_token_add_redirect(t_token *token, t_type type, size_t *i)
{
	t_redirect_param	*body;
	char				*head;

	if (type == REDIRECT_OUT || type == REDIRECT_IN)
		(*i)++;
	else if (type == APPEND_OUT || type == HERE_DOC)
		*i += 2;
	body = (t_redirect_param *) malloc(sizeof(t_redirect_param));
	if (errno)
		return ;
	body->body = cmd_token_get_redirect_body(token->value, i);
	if (errno)
	{
		free(body);
		return ;
	}
	body->fd[0] = -1;
	body->fd[1] = -1;
	head = cmd_token_get_redirect_head(type);
	cmd_token_add(&token->cmd_stack, type, head, body);
}

/**
 * @brief
 * Add a cmd_arg token from the value field of token to the cmd_arg stack.
 */
void	cmd_token_add_cmd_arg(t_token *token, t_cmd_arg **arg_stack, size_t *i)
{
	size_t	last_i;
	t_type	current_type;

	line_skip_space(token->value, i);
	last_i = *i;
	while (token->value[*i] && !ft_isspace(token->value[*i]))
	{
		line_skip_quote(token->value, i);
		current_type = cmd_token_get_type(token->value + *i);
		if (current_type != COMMAND)
		{
			if (last_i != *i)
				cmd_arg_add(arg_stack,
					ft_substr(token->value, last_i, *i - last_i));
			cmd_token_add_redirect(token, current_type, i);
			return ;
		}
		if (token->value[*i] != '\0')
			(*i)++;
	}
	if (last_i != *i)
		cmd_arg_add(arg_stack,
			ft_substr(token->value, last_i, *i - last_i));
}

/**
 * @brief
 * Add a command type token from the value field of token to the cmd_token stack.
 * Body is a cmd_arg stack and head is set to NULL
 */
void	cmd_token_add_command(t_token *token, t_cmd_arg *cmd_arg_stack)
{
	cmd_token_add(&token->cmd_stack, COMMAND, NULL, cmd_arg_stack);
}
