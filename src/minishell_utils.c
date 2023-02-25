/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:34:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/25 17:34:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "envp.h"
#include "token.h"

void	minishell_exit(t_hashtable *envp_dict, char *line,
			t_token *token_stack)
{
	if (envp_dict)
		hashtable_clear(envp_dict);
	if (line)
		free(line);
	if (token_stack)
		token_clear(token_stack);
	perror("minishell");
	exit(errno);
}

void	set_return_value(char *line)
{
	if (*line == '\0')
		g_return_value = 0;
	else
		g_return_value = 2;
	free(line);
}
