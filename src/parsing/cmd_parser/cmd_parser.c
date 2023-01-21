/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:04:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/20 04:04:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static bool	contain_cmd(t_cmd_token *head);
static void	place_cmd_top(t_cmd_token **cmd_stack);

char	*cmd_parse(t_cmd_token **cmd_stack)
{
	t_cmd_token	*head;

	if ((*cmd_stack)->type != COMMAND && contain_cmd(*cmd_stack) == true)
		place_cmd_top(cmd_stack);
	head = *cmd_stack;
	while (head->next != NULL)
	{
		if (head->type != COMMAND && *((char *) head->body) == '\0')
			return (head->next->head);
		head = head->next;
	}
	return (NULL);
}

static bool	contain_cmd(t_cmd_token *head)
{
	while (head != NULL)
	{
		if (head->type == COMMAND)
			return (true);
		head = head->next;
	}
	return (false);
}

static void	place_cmd_top(t_cmd_token **cmd_stack)
{
	t_cmd_token	*token;
	t_cmd_token	*cmd_token;

	token = *cmd_stack;
	while (token->next != NULL && token->next->type != COMMAND)
		token = token->next;
	cmd_token = token->next;
	token->next = cmd_token->next;
	cmd_token->next = *cmd_stack;
	*cmd_stack = cmd_token;
}
