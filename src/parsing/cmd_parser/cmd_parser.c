/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:04:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/20 04:04:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

int	cmd_parser(t_cmd_token *head)
{
	while (head != NULL)
	{
		if (head->type != COMMAND && ((t_redirect_param *) head->body)->body[0] == '\0')
		{
			if (head->next != NULL)
				return (error_syntax(head->next->head));
			else
				return (error_syntax("newline"));
		}
		head = head->next;
	}
	return (SUCCESS);
}
