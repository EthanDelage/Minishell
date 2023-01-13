/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:05:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/12 23:05:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

static char	*get_name(const char *envp_line)
{
	size_t	index;

	index = 0;
	while (envp_line[index] != '=')
		index++;
	return (ft_substr(envp_line, 0, index));
}

char	*get_value(const char *envp_line)
{
	size_t	end;
	size_t	start;

	start = 0;
	while (envp_line[start] != '=')
		start++;
	start++;
	end = start;
	while (envp_line[end] != '\0')
		end++;
	return (ft_substr(envp_line, start, end - start));
}

static t_dict	*parse_env_var(const char *envp_line)
{
	char	*name;
	char	*value;
	t_dict	*env_var;

	name = get_name(envp_line);
	if (errno)
		return (NULL);
	value = get_value(envp_line);
	if (errno)
		return (NULL);
	env_var = dict_new(name, value);
	return (env_var);
}

void	free_dict(t_dict **dict)
{
	size_t	index;

	index = 0;
	while (index < SIZE_HASHMAP)
	{
		clear_dict(&dict[index]);
		index++;
	}
}

t_dict	**parse_envp(char **envp)
{
	size_t	index;
	t_dict	**dict;
	t_dict	*env_var;

	dict = init_hashmap();
	if (dict == NULL)
		return (NULL);
	index = 0;
	while (envp[index] != NULL)
	{
		env_var = parse_env_var(envp[index]);
		if (errno)
		{
			free_dict(dict);
			return (NULL);
		}
		hash_elem(dict, env_var);
		index++;
	}
	return (dict);
}
