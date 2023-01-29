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

static size_t	count_nb_args(char **args);
static int		cd_no_args(t_hashtable *envp_dict);
static int		too_many_args(void);
static char		*replace_tilde(char *arg, t_hashtable *envp_dict);

int	builtin_cd(t_hashtable *envp_dict, char **args)
{
	const size_t	nb_args = count_nb_args(args);

	if (nb_args == 1)
		return (cd_no_args(envp_dict));
	else if (nb_args > 2)
		return (too_many_args());
	if (*(args[1]) == '~')
	{
		args[1] = replace_tilde(args[1], envp_dict);
		if (args[1] == NULL)
			return (1);
	}
	chdir(args[1]);
	if (errno)
	{
		builtin_print_error("cd", args[1]);
		perror(NULL);
		return (return_errno_error());
	}
	return (0);
}

static char	*replace_tilde(char *arg, t_hashtable *envp_dict)
{
	char	*path;
	t_dict	*home;

	home = hashtable_search(envp_dict, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	else
		path = ft_strjoin(home->value, arg + 1);
	free(arg);
	return (path);
}

static size_t	count_nb_args(char **args)
{
	size_t	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (count);
}

static int	cd_no_args(t_hashtable *envp_dict)
{
	t_dict	*home;

	home = hashtable_search(envp_dict, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	chdir(home->value);
	if (errno)
	{
		builtin_print_error("cd", home->value);
		perror(NULL);
		return (return_errno_error());
	}
	return (0);
}

static int	too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n",
		STDERR_FILENO);
	return (1);
}
