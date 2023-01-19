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

static void	sort_array(char **envp);
static void	swap_value(char **head);
static void	display_export(char **envp);
static int	builtin_export_no_args(t_hashtable *envp_dict);

int	builtin_export(t_hashtable *envp_dict, const char **args)
{
	if (args == NULL || *args == NULL)
		return (builtin_export_no_args(envp_dict));
	return (0);
}

static int	builtin_export_no_args(t_hashtable *envp_dict)
{
	char	**envp;

	envp = hashtable_get_array(envp_dict, true);
	if (errno)
		return (errno);
	sort_array(envp);
	display_export(envp);
	hashtable_array_clear(envp);
	return (0);
}

static void	display_export(char **envp)
{
	while (*envp != NULL)
	{
		printf("declare -x %s\n", *envp);
		envp++;
	}
}

static void	sort_array(char **envp)
{
	size_t	index;
	int		change;

	change = 1;
	if (*envp == NULL)
		return ;
	while (change)
	{
		change = 0;
		index = 0;
		while (envp[index + 1] != NULL)
		{
			if (ft_strcmp(envp[index], envp[index + 1]) > 0)
			{
				change = 1;
				swap_value(&envp[index]);
			}
			index++;
		}
	}
}

static void	swap_value(char **head)
{
	char	*tmp;

	tmp = head[0];
	*head = head[1];
	head[1] = tmp;
}
