/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_ret_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:36:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/26 15:36:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

static size_t	len_ret_value(unsigned char nb);
static void		fill_number(char *dest, unsigned char nb, size_t size_nb);

/**
 * @brief Replace "$?" by the g_return_value
 */
char	*replace_ret_value(char *line, size_t *index)
{
	const size_t	len_ret = len_ret_value(g_return_value);
	const size_t	len_line = ft_strlen(line);
	char			*new;

	new = (char *) malloc(sizeof(char) * (len_line + len_ret - 1));
	if (errno)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy((void *) new, (void *) line, *index);
	fill_number(new + *index, g_return_value, len_ret);
	ft_strcpy(new + *index + len_ret, line + *index + 2);
	*index = *index + len_ret;
	free(line);
	return (new);
}

static size_t	len_ret_value(unsigned char nb)
{
	if (nb > 9)
		return (len_ret_value(nb / 10) + 1);
	else
		return (1);
}

/**
 * @brief Add the return value in a string
 */
static void	fill_number(char *dest, unsigned char nb, size_t size_nb)
{
	while (size_nb != 0)
	{
		dest[size_nb - 1] = nb % 10 + '0';
		nb /= 10;
		size_nb--;
	}
}
