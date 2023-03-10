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
void		print_is_dir(char *name);

int	cmd_router(t_token *token, t_hashtable *envp_dict)
{
	if (token->cmd_stack->type != COMMAND)
		return (0);
	if (ft_strchr(token->cmd_stack->head, '/') != NULL)
		return (exec_path(token->cmd_stack, envp_dict));
	else if (is_builtin(token->cmd_stack) == true)
		return (exec_builtin(token, envp_dict));
	else
		exec_bin(token->cmd_stack, envp_dict);
	return (0);
}

int	exec_path(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	int		fd;
	char	**envp;
	char	**args;

	args = (char **) cmd_token->body;
	envp = hashtable_get_array(envp_dict, 0);
	if (errno)
		return (errno);
	fd = open(cmd_token->head, O_DIRECTORY);
	if (fd != -1)
		return (print_is_dir(cmd_token->head), close(fd),
			free_string_array(envp), 126);
	if (access(cmd_token->head, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd_token->head);
		if (errno == EACCES)
			return (free_string_array(envp), 126);
		return (free_string_array(envp), 127);
	}
	return (execve(cmd_token->head, args, envp));
}

int	exec_builtin(t_token *token, t_hashtable *envp_dict)
{
	char	**args;

	args = (char **) token->cmd_stack->body;
	if (ft_strcmp(token->cmd_stack->head, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(token->cmd_stack->head, "cd") == 0)
		return (builtin_cd(envp_dict, args));
	else if (ft_strcmp(token->cmd_stack->head, "env") == 0)
		return (builtin_env(envp_dict, args));
	else if (ft_strcmp(token->cmd_stack->head, "unset") == 0)
		return (builtin_unset(envp_dict, args));
	else if (ft_strcmp(token->cmd_stack->head, "export") == 0)
		return (builtin_export(envp_dict, args));
	else if (ft_strcmp(token->cmd_stack->head, "exit") == 0)
		return (builtin_exit(envp_dict, token, args));
	else if (ft_strcmp(token->cmd_stack->head, "echo") == 0)
		return (builtin_echo(args));
	return (EXIT_FAILURE);
}

void	exec_bin(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	char	**args;
	char	**envp;
	char	*cmd_path;

	args = (char **) cmd_token->body;
	cmd_path = cmd_find_path(cmd_token, envp_dict);
	if (cmd_path == NULL || *cmd_token->head == '\0')
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_token->head, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	envp = hashtable_get_array(envp_dict, 0);
	if (errno)
		exit(errno);
	execve(cmd_path, args, envp);
}

static char	*cmd_find_path(t_cmd_token *cmd_token, t_hashtable *envp_dict)
{
	char	**paths;
	char	*path;
	t_dict	*path_dict;

	path_dict = hashtable_search(envp_dict, "PATH");
	if (path_dict == NULL)
		return (NULL);
	paths = ft_split(path_dict->value, ':');
	if (errno)
		return (NULL);
	path = cmd_get_path(cmd_token, paths);
	if (path)
		return (free_string_array(paths), path);
	free_string_array(paths);
	return (NULL);
}
