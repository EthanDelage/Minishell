/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:16:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/23 09:16:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "router.h"

static char	*cmd_find_path(t_cmd_token *cmd_token, t_hashtable *envp_dict);
static int	exec_bin(t_cmd_token *cmd_token, t_hashtable *envp_dict);

int	cmd_router(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	char	**args;

	args = (char **) cmd_token->body;
	if (ft_strcmp(cmd_token->head, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd_token->head, "cd") == 0)
		return (builtin_cd(envp_dict, args));
	else if (ft_strcmp(cmd_token->head, "env") == 0)
		return (builtin_env(envp_dict));
	else if (ft_strcmp(cmd_token->head, "unset") == 0)
		return (builtin_unset(envp_dict, args));
	else if (ft_strcmp(cmd_token->head, "export") == 0)
		return (builtin_export(envp_dict, args));
	else
		return (exec_bin(cmd_token, envp_dict));
}

static int	exec_bin(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	char	**args;
	char	**envp;
	char	*cmd_path;

	args = (char **) cmd_token->body;
	cmd_path = cmd_find_path(cmd_token, envp_dict);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd_token->head, STDERR_FILENO);
		return (127);
	}
	envp = hashtable_get_array(envp_dict, 0);
	return (execve(cmd_path, args, envp));
}

static char	*cmd_find_path(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	char	**paths;
	char	*current_path;
	t_dict	*path_dict;

	path_dict = hashtable_search(envp_dict, "PATH");
	if (path_dict == NULL)
		return (NULL);
	paths = ft_split(path_dict->value, ':');
	while (*paths)
	{
		*paths = ft_strjoin(*paths, "/");
		current_path = ft_strjoin(*paths, cmd_token->head);
		if (access(current_path, X_OK) == 0)
			return (current_path);
		paths++;
	}
	return (NULL);
}

int	is_builtin(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	if (ft_strcmp(cmd_token->head, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_token->head, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_token->head, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_token->head, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_token->head, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_token->head, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_token->head, "exit") == 0)
		return (1);
	else if (cmd_find_path(cmd_token, envp_dict) != NULL)
		return (0);
	else
		return (-1);
}