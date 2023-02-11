/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:18:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 11:18:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "envp.h"
#include "replace.h"

extern unsigned char	g_return_value;

static char	*check_env_var_here_doc(t_hashtable *envp_dict, char *line,
				size_t *index);
static char	*replace_env_var(t_hashtable *envp_dict, char *line, size_t *index);
static char	*add_env_var(char *line, char *value, size_t *index,
				size_t end_index);

char	*here_doc_replace_env(t_hashtable *envp_dict, char *line)
{
	size_t	index;

	index = 0;
	if (line == NULL)
		return (ft_strdup(""));
	while (line[index])
	{
		if (line[index] == '$')
		{
			if (line[index + 1] == '?')
			{
				line = replace_ret_value(line, &index);
				if (errno)
					return (NULL);
			}
			line = check_env_var_here_doc(envp_dict, line, &index);
			if (errno)
				return (NULL);
		}
		else
			index++;
	}
	return (line);
}

static char	*check_env_var_here_doc(t_hashtable *envp_dict, char *line,
				size_t *index)
{
	if (!valid_char(line[*index + 1]))
		(*index)++;
	else
	{
		(*index)++;
		line = replace_env_var(envp_dict, line, index);
		if (errno)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

static char	*replace_env_var(t_hashtable *envp_dict, char *line, size_t *index)
{
	t_dict	*env;
	char	*name;
	size_t	end_index;

	end_index = *index;
	while (line[end_index] && !ft_isspace(line[end_index])
		&& line[end_index] != '"' && line[end_index] != '\''
		&& line[end_index] != '$')
		end_index++;
	name = ft_substr(line, *index, end_index - *index);
	if (errno)
	{
		free(line);
		return (NULL);
	}
	env = hashtable_search(envp_dict, name);
	if (env == NULL)
		line = add_env_var(line, "\0", index, end_index);
	else
		line = add_env_var(line, env->value, index, end_index);
	free(name);
	return (line);
}

static char	*add_env_var(char *line, char *value, size_t *index,
		size_t end_index)
{
	const size_t	len_value = ft_strlen(value);
	const size_t	len_line = ft_strlen(line);
	char			*end;
	char			*start;
	char			*new_line;

	new_line = (char *) malloc(sizeof(char)
			* (len_line + *index - end_index + len_value));
	if (errno)
	{
		free(line);
		return (NULL);
	}
	start = ft_substr(line, 0, *index - 1);
	end = ft_substr(line, end_index, len_line - end_index);
	new_line = ft_strjoin(start, value);
	new_line = ft_strjoin(new_line, end);
	*index = *index + len_value - 1;
	free(line);
	return (new_line);
}
