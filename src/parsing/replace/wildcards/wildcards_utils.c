/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:18:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 19:18:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

extern unsigned char	g_return_value;

/**
 * @brief Join two string with space between the two
 */
char	*strjoin_space(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	total_len;
	char	*new;

	if (s1)
		len_s1 = ft_strlen(s1);
	else
		return (ft_strdup(s2));
	total_len = len_s1 + ft_strlen(s2) + 2;
	new = (char *) malloc(sizeof(char) * total_len);
	if (errno)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy((void *) new, (void *) s1, len_s1);
	new[len_s1] = ' ';
	ft_strcpy(new + len_s1 + 1, s2);
	free(s1);
	return (new);
}

char	*wildcard_skip(char *str)
{
	while (*str && *str == '*')
		str++;
	return (str);
}

char	*error(char *template, char *result)
{
	if (template)
		free(template);
	if (result)
		free(result);
	perror("minishell");
	g_return_value = errno;
	errno = 0;
	return (NULL);
}
