/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:39:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 00:39:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

void	redirect_print_error(char *file_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
}

void	redirect_close(t_cmd_token *cmd_token)
{
	while (cmd_token)
	{
		if (cmd_token->type == REDIRECT_OUT)
			redirect_out_close((t_redirect_param *) cmd_token->body);
		if (cmd_token->type == REDIRECT_IN)
			redirect_in_close((t_redirect_param *) cmd_token->body);
		if (cmd_token->type == APPEND_OUT)
			append_out_close((t_redirect_param *) cmd_token->body);
		if (cmd_token->type == HERE_DOC)
			here_doc_close((t_redirect_param *) cmd_token->body);
		cmd_token = cmd_token->next;
	}
}

int	redirect_get_input_fd(t_cmd_token *head)
{
	int	fd;

	fd = -1;
	while (head)
	{
		if (head->type == REDIRECT_IN || head->type == HERE_DOC)
			fd = ((t_redirect_param *) head->body)->fd[READ];
		head = head->next;
	}
	return (fd);
}

int	redirect_get_output_fd(t_cmd_token *head)
{
	int	fd;

	fd = -1;
	while (head)
	{
		if (head->type == REDIRECT_OUT || head->type == APPEND_OUT)
			fd = ((t_redirect_param *) head->body)->fd[WRITE];
		head = head->next;
	}
	return (fd);
}
