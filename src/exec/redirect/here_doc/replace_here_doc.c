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
#include "redirect.h"

static char	*check_env_var_here_doc(t_hashtable *envp_dict, char *line,
				size_t *index);
static char	*replace_env_var(t_hashtable *envp_dict, char *line, size_t *index);
static char	*add_env_var(char *line, char *value, size_t *index,
				size_t end_index);
static char	*fill_env_var(char *start, char *end, char *value);

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

	start = ft_substr(line, 0, *index - 1);
	if (errno)
		return (free(line), NULL);
	end = ft_substr(line, end_index, len_line - end_index);
	free(line);
	if (errno)
		return (free(start), NULL);
	line = fill_env_var(start, end, value);
	if (errno)
		return (NULL);
	*index = *index + len_value - 1;
	return (line);
}

static char	*fill_env_var(char *start, char *end, char *value)
{
	char	*new_line;
	char	*tmp;

	tmp = ft_strjoin(start, value);
	free(start);
	if (errno)
		return (free(end), NULL);
	new_line = ft_strjoin(tmp, end);
	free(end);
	free(tmp);
	return (new_line);
}
