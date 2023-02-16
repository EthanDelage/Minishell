/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:39:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 08:39:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

int	redirect_in_open(t_redirect_param *redirect_param)
{
	redirect_param->fd[READ] = open(redirect_param->body, O_RDONLY);
	if (errno)
	{
		redirect_print_error(redirect_param->body);
		g_return_value = 1;
		perror(NULL);
		errno = 0;
		return (FAILURE);
	}
	return (0);
}

void	redirect_in_close(t_redirect_param *redirect_param)
{
	if (redirect_param->fd[READ] > 0)
		close(redirect_param->fd[READ]);
}
