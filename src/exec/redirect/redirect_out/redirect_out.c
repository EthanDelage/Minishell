/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:55:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 08:55:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

int	redirect_out_open(t_redirect_param *redirect_param)
{
	redirect_param->fd[WRITE] = open(redirect_param->body,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (errno)
	{
		redirect_print_error(redirect_param->body);
		g_return_value = 1;
		perror(NULL);
		errno = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	redirect_out_close(t_redirect_param *redirect_param)
{
	if (redirect_param->fd[WRITE] > 0)
		close(redirect_param->fd[WRITE]);
	redirect_param->fd[WRITE] = -1;
}
