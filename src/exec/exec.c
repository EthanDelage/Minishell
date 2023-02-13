/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:43:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/24 16:43:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "exec.h"

static t_token	*exec_router(t_token *head, t_hashtable *envp_dict);
static int		is_piped(t_token *head);
static t_token	*get_next_operator(t_token *head);

void	exec(t_token *head, t_hashtable *envp_dict)
{
	head = exec_router(head, envp_dict);
	while (head && head->type == OPERATOR)
	{
		if (*head->value == '&' && g_return_value == 0)
			head = exec_router(head->next, envp_dict);
		else if (*head->value == '|' && g_return_value != 0)
			head = exec_router(head->next, envp_dict);
		else
			head = get_next_operator(head->next);
	}
}

static t_token	*exec_router(t_token *head, t_hashtable *envp_dict)
{
	if (is_piped(head) == true)
		head = exec_pipe(head, envp_dict, STDIN_FILENO);
	else if (head->type == OPEN_PARENTHESIS)
		head = exec_subshell(head, envp_dict);
	else
		head = exec_cmd(head, envp_dict);
	if (errno)
		g_return_value = errno;
	return (head);
}

static int	is_piped(t_token *head)
{
	size_t	count_parenthesis;

	count_parenthesis = 0;
	while (head)
	{
		if (head->type == OPERATOR && count_parenthesis == 0)
			return (false);
		else if (head->type == PIPE && count_parenthesis == 0)
			return (true);
		else if (head->type == OPEN_PARENTHESIS)
			count_parenthesis++;
		else if (head->type == CLOSE_PARENTHESIS)
			count_parenthesis--;
		head = head->next;
	}
	return (false);
}

static t_token	*get_next_operator(t_token *head)
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
	return (head);
}
