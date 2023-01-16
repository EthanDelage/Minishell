/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:58:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/16 20:58:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "parser.h"

int	line_parser(t_token *head)
{
	int	count_parenthesis;
	int	missing;

	missing = -1;
	count_parenthesis = 0;
	if (head == NULL)
		return (missing);
	if (head->type != COMMAND && head->type != OPEN_PARENTHESIS)
		return (head->type);
	while (head->next != NULL)
	{
		if (head->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (head->type == CLOSE_PARENTHESIS)
		{
			if (count_parenthesis > 0)
				count_parenthesis--;
			else
				return (CLOSE_PARENTHESIS);
		}
		if (head->type == OPEN_PARENTHESIS && head->next->type != COMMAND)
			return (head->next->type);
		else if ((head->type == OPERATOR || head->type == PIPE) && (head->next->type != COMMAND && head->next->type != OPEN_PARENTHESIS))
			return (head->next->type);
		else if (head->type == CLOSE_PARENTHESIS && head->next->type == COMMAND)
			return (head->next->type);
		head = head->next;
	}
	if (head->type == CLOSE_PARENTHESIS && count_parenthesis > 0)
		count_parenthesis--;
	if (count_parenthesis > 0)
		return (OPEN_PARENTHESIS);
	return (-1);
}
