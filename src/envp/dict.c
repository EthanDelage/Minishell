/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:13:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/13 21:13:00 by edelage          ###   ########lyon.fr   */
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

static char	*get_value(const char *envp_line)
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
	t_dict	*env_var;

	env_var = (t_dict *) malloc(sizeof(t_dict));
	if (env_var == NULL)
		return (NULL);
	env_var->name = get_name(envp_line);
	if (env_var->name == NULL)
	{
		free(env_var);
		return (NULL);
	}
	env_var->value = get_value(envp_line);
	if (env_var->name == NULL)
	{
		free(env_var->value);
		free(env_var);
		return (NULL);
	}
	env_var->next = NULL;
	return (env_var);
}

t_hashtable	*envp_to_dict(char **envp)
{
	t_hashtable	*hashtable;
	t_dict		*env_var;
	size_t		index;

	hashtable = hashtable_init(SIZE_HASHTABLE);
	if (hashtable == NULL)
		return (NULL);
	index = 0;
	while (envp[index] != NULL)
	{
		env_var = parse_env_var(envp[index]);
		if (env_var == NULL)
		{
			hashtable_clean(hashtable);
			return (NULL);
		}
		hashtable_push(hashtable, env_var);
		index++;
	}
	return (hashtable);
}
