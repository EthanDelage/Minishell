/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:26:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 18:26:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

static char	*wildcard_get_file(char *template, DIR *dir);
static bool	wildcard_is_valid(char *filename, char *template);

char	*wildcard_replace(char *template)
{
	DIR				*dir;
	char			*result;

	result = NULL;
	dir = opendir(".");
	if (errno)
		return (wildcard_error(template, result));
	result = wildcard_get_file(template, dir);
	if (errno)
		return (wildcard_error(template, result));
	if (closedir(dir) == -1)
		return (wildcard_error(template, result));
	if (result == NULL)
		return (template);
	free(template);
	return (result);
}

t_cmd_arg	*replace_split_wildcard(t_cmd_arg *head, t_cmd_arg *delimiter)
{
	while (head && head != delimiter)
	{
		head->arg = wildcard_replace(head->arg);
		if (errno)
			return (NULL);
		head = split_arg(head);
		if (errno)
			return (NULL);
	}
	return (head);
}

static char	*wildcard_get_file(char *template, DIR *dir)
{
	struct dirent	*entry;
	char			*result;

	result = NULL;
	entry = readdir(dir);
	if (errno)
		return (NULL);
	while (entry)
	{
		if (wildcard_is_valid(entry->d_name, template)
			&& (entry->d_name[0] != '.'
				|| (entry->d_name[0] == '.' && template[0] == '.')))
		{
			result = strjoin_space(result, entry->d_name);
			if (errno)
				return (NULL);
		}
		entry = readdir(dir);
		if (errno)
			return (NULL);
	}
	return (result);
}

static bool	wildcard_is_valid(char *filename, char *template)
{
	while (*template)
	{
		if (*template == '*')
		{
			template = wildcard_skip(template);
			if (*template == 0)
				return (true);
			filename = ft_strchr(filename, *template);
			if (filename == NULL)
				return (false);
		}
		else if (*template != *filename)
			return (false);
		filename++;
		template++;
	}
	if (*filename != '\0')
		return (false);
	return (true);
}
