/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:52:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/22 08:52:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

static size_t	nb_args(char **args);

int	builtin_cd(char **args)
{
	if (nb_args(args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n",
			STDERR_FILENO);
		return (1);
	}
	chdir(args[1]);
	if (errno)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(args[1]);
		errno = 0;
		return (1);
	}
	return (0);
}

static size_t	nb_args(char **args)
{
	size_t	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

