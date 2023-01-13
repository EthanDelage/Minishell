/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:46:28 by edelage           #+#    #+#             */
/*   Updated: 2022/10/11 18:19:26 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void	init_str(char *str, size_t size)
{
	size_t	count;

	count = 0;
	while (count < size)
	{
		str[count] = '\0';
		count++;
	}
}

int	strichr(const char *str, int c)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	if (str[index] == c)
		return (index);
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	size_t	index;
	size_t	len_s;

	index = 0;
	len_s = ft_strlen(s);
	if ((start + len) > len_s)
		len = len_s - start;
	fresh = (char *) malloc(sizeof(char) * (len + 1));
	if (fresh == NULL)
		return (NULL);
	while (index < len)
	{
		fresh[index] = s[start + index];
		index++;
	}
	fresh[index] = '\0';
	return (fresh);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (size != 0)
	{
		while (src[index] && index < (size - 1))
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (ft_strlen(src));
}
