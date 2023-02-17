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
static void		strcat_trimmed_quotes(const char *src, char *dst);

/**
 * @brief Trim the quotes as bash do.
 */
char	*trim_quotes(char *str)
{
	char	*trimmed_str;
	size_t	final_size;

	final_size = ft_strlen(str) - count_trimmed_quotes(str);
	trimmed_str = (char *) malloc((final_size + 1) * sizeof (char));
	if (trimmed_str == NULL)
	{
		free(str);
		return (NULL);
	}
	strcat_trimmed_quotes(str, trimmed_str);
	free(str);
	return (trimmed_str);
}

/**
 * @brief Concatenate string without the quotes.
 */
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
	char	quote;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			count++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				count++;
		}
		i++;
	}
	return (count);
}
