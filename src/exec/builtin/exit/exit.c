/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:52:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/27 15:52:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

static int	is_numeric_arg(char *arg);

int	builtin_exit(t_hashtable *envp_dict, t_token *token_stack, char **args)
{
	if (args[1] && args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (envp_dict)
		hashtable_clear(envp_dict);
	if (token_stack)
		token_clear(&token_stack);
	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric_arg(args[1]))
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(ft_atoi(args[1]));
	}
	exit(0);
}

static int	is_numeric_arg(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}