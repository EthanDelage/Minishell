/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_line_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:59:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/17 13:59:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "parser.h"

int	error_syntax(char *value)
{
	if (value != NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}
