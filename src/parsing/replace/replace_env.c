/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:03:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/16 18:03:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

static char	*check_env_var(t_hashtable *envp_dict, char *line, size_t *index,
				char *quote);
static void	change_quote_value(char *quote, char c);
static char	*replace_env_var(t_hashtable *envp_dict, char *line, size_t *index);
static char	*add_env_var(char *line, char *value, size_t *index,
				size_t end_index);

/**
 * @brief Replace env variable in line
 */
char	*replace_env(t_hashtable *envp_dict, char *line)
{
	size_t	index;
	char	quote;

	index = 0;
	quote = 0;
	while (line[index])
	{
		if (line[index] == '$' && quote != '\'')
		{
			if (line[index + 1] == '?')
				line = replace_ret_value(line, &index);
			else
				line = check_env_var(envp_dict, line, &index, &quote);
			if (errno)
				return (NULL);
		}
		else
		{
			if (line[index] == '"' || line[index] == '\'')
				change_quote_value(&quote, line[index]);
			index++;
		}
	}
	return (line);
}

/**
 * @brief Replace env var if it's a good syntax
 */
static char	*check_env_var(t_hashtable *envp_dict, char *line, size_t *index,
				char *quote)
{
	if ((*quote == '"' || *quote == '\0') && !valid_char(line[*index + 1]) && !(*quote == '\0' && (line[*index + 1] == '"' || line[*index + 1] == '\'')))
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

static void	change_quote_value(char *quote, char c)
{
	if (c == '"')
	{
		if (*quote == '"')
			*quote = 0;
		else if (*quote == 0)
			*quote = '"';
	}
	else
	{
		if (*quote == '\'')
			*quote = 0;
		else if (*quote == 0)
			*quote = '\'';
	}
}

static char	*replace_env_var(t_hashtable *envp_dict, char *line, size_t *index)
{
	t_dict	*env;
	char	*name;
	size_t	end_index;

	end_index = *index;
	if (!ft_isdigit(line[end_index]))
	{
		while (line[end_index] && !ft_isspace(line[end_index])
			   && line[end_index] != '"' && line[end_index] != '\''
			   && line[end_index] != '$' && valid_char(line[end_index]))
			end_index++;
	}
	else
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
