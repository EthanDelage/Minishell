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

#include "mini_signal.h"

static int	is_numeric_arg(char *arg);
static void	exit_properly(long long return_value, t_hashtable *envp_dict, t_token *token_stack, char **args);

/**
 * @brief Cause the shell to exit
 */
int	builtin_exit(t_hashtable *envp_dict, t_token *token_stack, char **args)
{
	long long	return_value;

	errno = 0;
	return_value = 0;
	if (args && *args && args[1])
	{
		return_value = ft_atoll(args[1]);
		if (!is_numeric_arg(args[1]) || errno)
			exit_properly(2, envp_dict, token_stack, args);
		else if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	exit_properly(return_value, envp_dict, token_stack, NULL);
	return (0);
}

static void	exit_properly(long long return_value, t_hashtable *envp_dict, t_token *token_stack, char **args)
{
	printf("exit\n");
	if (return_value == 2 && errno)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	if (envp_dict)
		hashtable_clear(envp_dict);
	if (token_stack)
		token_clear(token_stack);
	exit((unsigned char) return_value);
}

static int	is_numeric_arg(char *arg)
{
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
		{
			errno = EINVAL;
			return (false);
		}
		arg++;
	}
	return (true);
}
