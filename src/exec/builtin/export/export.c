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

int			builtin_export_no_args(t_hashtable *envp_dict);
static void	export_one(t_hashtable *envp_dict, const char *env);
static int	valid_env(const char *env);
static int	non_export_env(char *env);

/**
 * @brief Set the export attribute for variables
 */
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
		if (!ft_isdigit(*args[index])
			&& non_export_env(args[index]) == true)
			;
		else if (valid_env(args[index]) == false)
		{
			builtin_print_error("export", args[index]);
			ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
			return_value = 1;
		}
		else
			export_one(envp_dict, args[index]);
		index++;
	}
	if (errno)
		return (return_errno_error());
	return (return_value);
}

static void	export_one(t_hashtable *envp_dict, const char *env)
{
	t_dict	*env_var;
	t_dict	*elem;

	env_var = parse_env_var(env);
	if (errno)
		return ;
	elem = hashtable_search(envp_dict, env_var->name);
	if (elem != NULL)
	{
		env_var->value = hashtable_set(elem, env_var->value);
		dict_free_elem(&env_var);
	}
	else
		hashtable_push(envp_dict, env_var);
}

static int	valid_env(const char *env)
{
	size_t	index;

	index = 0;
	if (ft_isdigit(env[index]) || env[0] == '\0')
		return (false);
	while (valid_char(env[index]))
		index++;
	if (index == 0 || env[index] != '=')
		return (false);
	return (true);
}

static int	non_export_env(char *env)
{
	if (*env == 0)
		return (false);
	while (valid_char(*env))
		env++;
	if (*env != 0)
		return (false);
	return (true);
}
