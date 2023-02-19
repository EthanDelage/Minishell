/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:17:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/14 18:17:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

static bool	valid_name(const char *name);

/**
 * @brief Unset values and attributes of variables
 */
int	builtin_unset(t_hashtable *envp_dict, char **args)
{
	size_t	index;
	int		return_value;

	index = 1;
	return_value = 0;
	while (args[index] != NULL)
	{
		if (valid_name(args[index]) == false)
		{
			builtin_print_error("unset", args[index]);
			ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
			return_value = 1;
		}
		else
			hashtable_remove_one(envp_dict, args[index]);
		index++;
	}
	return (return_value);
}

static bool	valid_name(const char *name)
{
	size_t	index;

	index = 0;
	if (ft_isdigit(name[index]) || name[index] == '\0')
		return (false);
	while (name[index] != '\0')
	{
		if (!valid_char(name[index]))
			return (false);
		index++;
	}
	return (true);
}

int	valid_char(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == '_');
}
