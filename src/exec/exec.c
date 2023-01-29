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

int	exec(t_token *head, t_hashtable *envp_dict, int std_fd[2])
{
	int	pid;
	int	return_value;

	if (head->next && head->next->type == PIPE)
	{
	}
}
