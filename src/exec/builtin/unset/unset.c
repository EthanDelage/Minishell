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

static int	valid_name(const char *name);

int	builtin_unset(t_hashtable *envp_dict, char **args)
{
	size_t	count;
	int		return_value;

	count = 1;
	return_value = 0;
	while (args[count] != NULL)
	{
		if (valid_name(args[count]) == false)
		{
			printf("minishell: unset: `%s': invalid parameter name\n",
				args[count]);
			return_value = 1;
		}
		else
			hashtable_remove_one(envp_dict, args[count]);
		count++;
	}
	return (return_value);
}

static int	valid_name(const char *name)
{
	size_t	index;

	index = 0;
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
