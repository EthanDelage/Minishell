/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:11:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/24 08:11:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

static size_t	count_trimmed_quotes(const char *str);
static	void	strcat_trimmed_quotes(const char *src, char *dst);

char	*trim_quotes(char *str)
{
	char	*trimmed_str;
	size_t	final_size;

	final_size = ft_strlen(str) - count_trimmed_quotes(str);
	trimmed_str = (char *) malloc(final_size * sizeof (char));
	if (trimmed_str == NULL)
		return (NULL);
	strcat_trimmed_quotes(str, trimmed_str);
	free(str);
	return (trimmed_str);
}

static	void	strcat_trimmed_quotes(const char *src, char *dst)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			i++;
			while (src[i] && src[i] != '\'')
				dst[j++] = src[i++];
		}
		else if (src[i] == '"')
		{
			i++;
			while (src[i] && src[i] != '"')
				dst[j++] = src[i++];
		}
		else
			dst[j++] = src[i];
		i++;
	}
	dst[j] = 0;
}

static size_t	count_trimmed_quotes(const char *str)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			count++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
				count++;
		}
		else if (str[i] == '\'')
		{
			i++;
			count++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				count++;
		}
		i++;
	}
	return (count);
}
