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

void	init_pipe(int fd_pipe[2])
{
	fd_pipe[READ] = -1;
	fd_pipe[WRITE] = -1;
}

void	close_pipe(int fd_pipe[2])
{
	close(fd_pipe[READ]);
	close(fd_pipe[WRITE]);
}

int	is_exec_minishell(char *path)
{
	const size_t	len = ft_strlen(path);

	if (len > 9 && ft_strcmp("minishell", path + len - 9) == 0)
		return (true);
	return (false);
}

void	init_ret_val(t_ret_val *ret_val)
{
	ret_val->ret_val = -1;
	ret_val->last_cmd_sig = false;
}
