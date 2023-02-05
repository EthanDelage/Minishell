/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:36:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 08:36:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

static int	redirect_close_error(t_cmd_token *head, t_cmd_token *node_error);
static int	cmd_here_doc_open(t_cmd_token *cmd_token);
static void	cmd_here_doc_close_error(t_token *head, t_cmd_token *node_error);

int	redirect_open(t_hashtable *envp_dict, t_cmd_token *cmd_token)
{
	t_cmd_token	*head;
// TODO: close all not use redirect before exec_cmd
	head = cmd_token;
	while (cmd_token)
	{
		if (cmd_token->type == REDIRECT_OUT)
			if (redirect_out_open((t_redirect_param *) cmd_token->body) != 0)
				return (redirect_close_error(head, cmd_token));
		if (cmd_token->type == REDIRECT_IN)
			if (redirect_in_open((t_redirect_param *) cmd_token->body) != 0)
				return (redirect_close_error(head, cmd_token));
		if (cmd_token->type == APPEND_OUT)
			if (append_out_open((t_redirect_param *) cmd_token->body) != 0)
				return (redirect_close_error(head, cmd_token));
		if (cmd_token->type == HERE_DOC)
			if (here_doc_write(envp_dict,
					(t_redirect_param *) cmd_token->body) != 0)
				return (redirect_close_error(head, cmd_token));
		cmd_token = cmd_token->next;
	}
	return (EXIT_SUCCESS);
}

int	here_doc_get(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == COMMAND)
		{
			if (cmd_here_doc_open(current->cmd_stack) == 1)
			{
				cmd_here_doc_close_error(head, current->cmd_stack);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

static int	cmd_here_doc_open(t_cmd_token *cmd_token)
{
	while (cmd_token)
	{
		if (cmd_token->type == HERE_DOC)
			if (here_doc_open((t_redirect_param *) cmd_token->body) != 0)
				return (1);
		cmd_token = cmd_token->next;
	}
	return (0);
}

static void	cmd_here_doc_close_error(t_token *head, t_cmd_token *node_error)
{
	t_cmd_token	*save;
	t_cmd_token	*tmp;

	while (head)
	{
		if (head->type == COMMAND)
		{
			tmp = head->cmd_stack;
			save = tmp;
			while (tmp)
			{
				if (tmp->type == HERE_DOC)
					here_doc_close_error((t_redirect_param *) tmp->body);
				tmp = tmp->next;
			}
			if (save == node_error)
				return ;
		}
		head = head->next;
	}
}

static int	redirect_close_error(t_cmd_token *head, t_cmd_token *node_error)
{
	while (head && head != node_error)
	{
		if (head->type == REDIRECT_OUT)
			redirect_out_close((t_redirect_param *) head->body);
		if (head->type == REDIRECT_IN)
			redirect_in_close((t_redirect_param *) head->body);
		if (head->type == APPEND_OUT)
			append_out_close((t_redirect_param *) head->body);
		if (head->type == HERE_DOC)
			here_doc_close((t_redirect_param *) head->body);
		head = head->next;
	}
	return (EXIT_FAILURE);
}
