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

static int	valid_char(char c);
static int	valid_name(const char *name);

int	builtin_unset(t_hashtable *envp_dict, const char **args)
{
	size_t	count;
	int		return_value;

	if (args == NULL || *args == NULL)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	count = 0;
	return_value = 0;
	while (args[count] != NULL)
	{
		if (valid_name(args[count]) != 0)
		{
			printf("unset: \"%s\": invalid parameter name\n", args[count]);
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
	size_t	count;

	count = 0;
	while (name[count] != '\0')
	{
		if (!valid_char(name[count]))
			return (1);
		count++;
	}
	return (0);
}

static int	valid_char(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == '_');
}
