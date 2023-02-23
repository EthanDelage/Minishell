/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 00:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

void	here_doc_close(t_redirect_param *redirect_param)
{
	if (redirect_param->fd[READ] > 0)
		close(redirect_param->fd[READ]);
}

void	here_doc_close_error(t_redirect_param *redirect_param)
{
	here_doc_close(redirect_param);
	if (redirect_param->fd[WRITE] > 0)
		close(redirect_param->fd[WRITE]);
}

void	here_doc_warning(char *delimiter)
{
	printf("minishell: warning: here-document delimited by "
		"end-of-file (wanted `%s')\n", delimiter);
}
