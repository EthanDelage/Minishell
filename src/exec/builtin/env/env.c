/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:55:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/16 11:55:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

static void	display_env(char **envp);

int	builtin_env(t_hashtable *envp_dict)
{
	char	**envp;

	envp = hashtable_get_array(envp_dict);
	if (errno)
		return (errno);
	display_env(envp);
	hashtable_array_clear(envp);
	return (0);
}

static void	display_env(char **envp)
{
	size_t	index;

	index = 0;
	while (envp[index] != NULL)
	{
		printf("%s\n", envp[index]);
		index++;
	}
}
