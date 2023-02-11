/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:20:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 09:20:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

int	append_out_open(t_redirect_param *redirect_param)
{
	redirect_param->fd[WRITE] = open(redirect_param->body, O_WRONLY
			| O_APPEND | O_CREAT, 0644);
	if (errno)
	{
		redirect_print_error(redirect_param->body);
		perror(NULL);
		return (return_errno_error());
	}
	return (SUCCESS);
}

void	append_out_close(t_redirect_param *redirect_param)
{
	if (redirect_param->fd[WRITE] > 0)
		close(redirect_param->fd[WRITE]);
}
