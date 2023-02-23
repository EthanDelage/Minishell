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

/**
 * @brief Close unused fd before executing command
 */
void	redirect_close_unused(t_cmd_token *cmd_token, int fd_io[2])
{
	while (cmd_token)
	{
		if (cmd_token->type == REDIRECT_OUT
			&& fd_io[WRITE] != ((t_redirect_param *)cmd_token->body)->fd[WRITE])
			redirect_out_close((t_redirect_param *)cmd_token->body);
		if (cmd_token->type == REDIRECT_IN
			&& fd_io[READ] != ((t_redirect_param *)cmd_token->body)->fd[READ])
			redirect_in_close((t_redirect_param *)cmd_token->body);
		if (cmd_token->type == APPEND_OUT
			&& fd_io[WRITE] != ((t_redirect_param *)cmd_token->body)->fd[WRITE])
			append_out_close((t_redirect_param *)cmd_token->body);
		if (cmd_token->type == HERE_DOC
			&& fd_io[READ] != ((t_redirect_param *)cmd_token->body)->fd[READ])
			here_doc_close((t_redirect_param *)cmd_token->body);
		cmd_token = cmd_token->next;
	}
}
