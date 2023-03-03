/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:19:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/25 17:19:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

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

void	reset_stdio(int fd_save[2])
{
	if (fd_save[READ] != -1 && fd_save[READ] != STDIN_FILENO)
		if (dup2_fd(fd_save[READ], STDIN_FILENO) == EXIT_FAILURE)
			return ;
	if (fd_save[WRITE] != -1 && fd_save[WRITE] != STDOUT_FILENO)
		if (dup2_fd(fd_save[WRITE], STDOUT_FILENO) == EXIT_FAILURE)
			return ;
}
