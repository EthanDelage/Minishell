/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:45:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 00:45:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "router.h"

int	is_builtin(t_cmd_token *cmd_token)
{
	const char	*builtin[] = {"pwd", "cd", "env", "unset",
		"export", "exit", "echo", NULL};
	size_t		index;

	index = 0;
	if (ft_strchr(cmd_token->head, '/') != NULL)
		return (0);
	while (builtin[index] != NULL)
	{
		if (ft_strcmp(cmd_token->head, builtin[index]) == 0)
			return (1);
		index++;
	}
	return (0);
}
