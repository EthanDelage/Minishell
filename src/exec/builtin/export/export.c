/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:28:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/18 18:28:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

static int	valid_env(const char *env);
static void	export_one(t_hashtable *envp_dict, const char *env);

int	builtin_export(t_hashtable *envp_dict, char **args)
{
	size_t	index;
	int		return_value;

	if (args[1] == NULL)
		return (builtin_export_no_args(envp_dict));
	index = 1;
	return_value = 0;
	while (args[index])
	{
		if (valid_env(args[index]) == false)
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				args[index]);
			return_value = 1;
		}
		else
		{
			export_one(envp_dict, args[index]);
			if (errno)
				return (errno);
		}
		index++;
	}
	return (return_value);
}

static void	export_one(t_hashtable *envp_dict, const char *env)
{
	t_dict	*env_var;

	env_var = parse_env_var(env);
	if (errno)
		return ;
	hashtable_push(envp_dict, env_var);
}

static int	valid_env(const char *env)
{
	size_t	index;

	index = 0;
	while (valid_char(env[index]))
		index++;
	if (index == 0 || env[index] != '=')
		return (false);
	return (true);
}
