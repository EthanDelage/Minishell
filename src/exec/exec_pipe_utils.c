/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:38:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/12 17:38:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

/**
 * @brief Get the next piped command token
 */
t_token	*get_next_pipe(t_token *head)
{
	size_t	count_parenthesis;

	count_parenthesis = 0;
	while (head)
	{
		if (head->type == OPERATOR && count_parenthesis == 0)
			return (NULL);
		else if (head->type == PIPE && count_parenthesis == 0)
			return (head->next);
		else if (head->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (head->type == CLOSE_PARENTHESIS)
			count_parenthesis--;
		head = head->next;
	}
	return (NULL);
}

/**
 * @brief Get the operator after all pipe if it exist
 */
t_token	*get_next_cmd(t_token *head)
{
	size_t	count_parenthesis;

	count_parenthesis = 0;
	while (head)
	{
		if (head->type == OPERATOR && count_parenthesis == 0)
			return (head);
		else if (head->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (head->type == CLOSE_PARENTHESIS)
			count_parenthesis--;
		head = head->next;
	}
	return (NULL);
}

void	close_pipe(int fd_pipe[2])
{
	close(fd_pipe[READ]);
	close(fd_pipe[WRITE]);
}
