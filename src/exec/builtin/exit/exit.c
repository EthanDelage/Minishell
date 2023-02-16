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
static void	exit_handle_arg(char *arg);
static char	*exit_get_arg(char **args);

int	builtin_exit(t_hashtable *envp_dict, t_token *token_stack, char **args)
{
	char				*arg;

	if (args && args[1] && args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (envp_dict)
		hashtable_clear(envp_dict);
	arg = exit_get_arg(args);
	if (token_stack)
		token_clear(token_stack);
	printf("exit\n");
	if (arg)
		exit_handle_arg(arg);
	exit(0);
}

static void	exit_handle_arg(char *arg)
{
	long long	return_value;

	return_value = ft_atoll((arg));
	if (!is_numeric_arg(arg) || errno)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free(arg);
		exit (2);
	}
	free(arg);
	exit((unsigned char)return_value);
}

static char	*exit_get_arg(char **args)
{
	char	*arg;
	size_t	size;

	if (args && args[1])
	{
		size = ft_strlen(args[1]);
		arg = (char *) malloc((size + 1) * sizeof (char));
		ft_memcpy(arg, args[1], size + 1);
		return (arg);
	}
	return (NULL);
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
			return (0);
		arg++;
	}
	return (1);
}
