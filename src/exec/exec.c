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

static t_token	*exec_router(t_token **head, t_hashtable *envp_dict);
static int		is_piped(t_token *head);
static t_token	*get_next_operator(t_token *head);

void	exec(t_token **head, t_hashtable *envp_dict)
{
	t_token	*tmp;

	*head = exec_router(head, envp_dict);
	while (*head && (*head)->type == OPERATOR)
	{
		if (pwd_set(envp_dict) == FAILURE)
			return ;
		if ((*(*head)->value == '&' && g_return_value == 0)
			|| (*(*head)->value == '|' && g_return_value != 0))
		{
			tmp = (*head)->next;
			token_clear_until(head, tmp);
			*head = exec_router(&tmp, envp_dict);
		}
		else
		{
			tmp = get_next_operator((*head)->next);
			token_clear_until(head, tmp);
		}
	}
}

static t_token	*exec_router(t_token **head, t_hashtable *envp_dict)
{
	t_token	*tmp;

	if (is_piped(*head) == true)
		tmp = exec_pipe(head, envp_dict, STDIN_FILENO);
	else if ((*head)->type == OPEN_PARENTHESIS)
		tmp = exec_subshell(head, envp_dict);
	else
		tmp = exec_cmd(*head, envp_dict);
	if (errno && errno != EINTR)
		g_return_value = errno;
	errno = 0;
	token_clear_until(head, tmp);
	return (tmp);
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
