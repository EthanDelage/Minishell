/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:47:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/30 22:47:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

static int	echo_handle_option(char **args);
static int	echo_put_args(char **args);
static int	is_endl_option(char *arg);

int	builtin_echo(char **args)
{
	args++;
	if (args && is_endl_option(*args))
		return (echo_handle_option(args));
	if (echo_put_args(args) == 1)
		return (1);
	if (printf("\n") <= 0)
		return (1);
	return (0);
}

static int	echo_handle_option(char **args)
{
	while (is_endl_option(*args))
		args++;
	return (echo_put_args(args));
}

static int	echo_put_args(char **args)
{
	while (*args)
	{
		if (printf("%s", *args) <= 0)
			return (1);
		args++;
		if (args)
			if (printf(" ") <= 0)
				return (1);
	}
	return (0);
}

static int	is_endl_option(char *arg)
{
	if (*arg != '-')
		return (0);
	arg++;
	if (*arg == '\0')
		return (0);
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}
