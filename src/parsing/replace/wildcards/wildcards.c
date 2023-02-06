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

static char	*wildcard_skip(char *str);

bool	wildcard_is_valid(char *filename, char *template)
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
	return (true);
}

static char	*wildcard_skip(char *str)
{
	while (*str && *str == '*')
		str++;
	return (str);
}