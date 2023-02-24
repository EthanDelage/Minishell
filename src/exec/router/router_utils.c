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

bool	is_builtin(t_cmd_token *cmd_token)
{
	const char	*builtin[] = {"pwd", "cd", "env", "unset",
		"export", "exit", "echo", NULL};
	size_t		index;

	index = 0;
	if (ft_strchr(cmd_token->head, '/') != NULL)
		return (false);
	while (builtin[index] != NULL)
	{
		if (ft_strcmp(cmd_token->head, builtin[index]) == 0)
			return (true);
		index++;
	}
	return (false);
}

void	print_is_dir(char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

char	*cmd_get_path(t_cmd_token *cmd_token, char **paths)
{
	char	*current_path;
	size_t	index;

	index = 0;
	while (paths[index])
	{
		current_path = ft_strjoin(paths[index], "/");
		if (errno)
			return (NULL);
		free(paths[index]);
		paths[index] = current_path;
		current_path = ft_strjoin(paths[index], cmd_token->head);
		if (errno)
			return (NULL);
		if (access(current_path, X_OK) == 0)
			return (current_path);
		errno = 0;
		free(current_path);
		index++;
	}
	return (NULL);
}
