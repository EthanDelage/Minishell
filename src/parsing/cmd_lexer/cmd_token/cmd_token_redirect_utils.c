/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token_add_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:24:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/20 00:24:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_token.h"

char *cmd_token_get_redirect_head(int type)
{
	if (type == REDIRECT_OUT)
		return (">");
	if (type == REDIRECT_IN)
		return ("<");
	if (type == APPEND_OUT)
		return (">>");
	if (type == HERE_DOC)
		return ("<<");
	return (NULL);
}

char	*cmd_token_get_redirect_body(char *cmd_line, size_t *i)
{
	size_t	last_i;
	char	*body;

	last_i = *i;
	line_trim_space(cmd_line, i);
	while (!ft_strchr("\t\v\n\f\r ", cmd_line[*i]))
		(*i)++;
	body = ft_substr(cmd_line, last_i, *i - last_i);
	return (body);
}