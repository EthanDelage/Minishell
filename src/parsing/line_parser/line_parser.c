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

static int	check_parenthesis(t_token *token, int *count);
static int	check_error(t_token *head);

char	*line_parser(t_token *head)
{
	int	count_parenthesis;

	count_parenthesis = 0;
	if (head == NULL)
		return (NULL);
	if (head->type != COMMAND && head->type != OPEN_PARENTHESIS)
		return (head->value);
	while (head->next != NULL)
	{
		if (check_parenthesis(head, &count_parenthesis) == FAILURE)
			return (head->value);
		if (check_error(head) == FAILURE)
			return (head->next->value);
		head = head->next;
	}
	if (head->type == CLOSE_PARENTHESIS && count_parenthesis > 0)
		count_parenthesis--;
	if (count_parenthesis > 0)
		return ("(");
	return (NULL);
}

static int	check_parenthesis(t_token *token, int *count)
{
	if (token->type == OPEN_PARENTHESIS)
		(*count)++;
	else if (token->type == CLOSE_PARENTHESIS)
	{
		if (*count > 0)
			(*count)--;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_error(t_token *head)
{
	if (head->type == OPEN_PARENTHESIS
		&& head->next->type != COMMAND && head->next->type != OPEN_PARENTHESIS)
		return (FAILURE);
	else if ((head->type == OPERATOR || head->type == PIPE)
		&& (head->next->type != COMMAND
			&& head->next->type != OPEN_PARENTHESIS))
		return (FAILURE);
	else if (head->type == CLOSE_PARENTHESIS
		&& (head->next->type == COMMAND
			|| head->next->type == OPEN_PARENTHESIS))
		return (FAILURE);
	return (SUCCESS);
}