/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:47:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/28 00:47:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "replace.h"

static int	replace_cmd(t_hashtable *envp_dict, t_cmd_token *cmd_token);
static int	replace_cmd_arg(t_hashtable *envp_dict, t_cmd_arg *args);
static int	replace_redirect(t_hashtable *envp_dict,
				t_cmd_token *redirect_token);
static bool	is_ambiguous_redirect(char *file_name);

/**
 * @brief Replace env variables by their value.
 */
int	replace(t_hashtable *envp_dict, t_cmd_token *head)
{
	t_cmd_token	*token;

	token = head;
	while (token)
	{
		if (token->type == COMMAND)
		{
			if (replace_cmd(envp_dict, token) == FAILURE)
				return (FAILURE);
		}
		else if (token->type != HERE_DOC)
		{
			if (replace_redirect(envp_dict, token) == FAILURE)
				return (FAILURE);
		}
		token = token->next;
	}
	return (SUCCESS);
}

/**
 * @brief Convert cmd_arg_stack to an array of string while overriding  env var
 */
static int	replace_cmd(t_hashtable *envp_dict, t_cmd_token *cmd_token)
{
	t_cmd_arg	*arg_stack;

	if (replace_cmd_arg(envp_dict, (t_cmd_arg *) cmd_token->body) == FAILURE)
		return (FAILURE);
	remove_empty_arg((t_cmd_arg **) &(cmd_token->body));
	if (cmd_arg_remove_quote((t_cmd_arg *) cmd_token->body) == FAILURE)
		return (FAILURE);
	cmd_arg_reverse((t_cmd_arg **) &cmd_token->body);
	free(cmd_token->head);
	if (cmd_token->body == NULL)
		return (SUCCESS);
	cmd_token->head = ft_strdup(((t_cmd_arg *) cmd_token->body)->arg);
	arg_stack = (t_cmd_arg *) cmd_token->body;
	cmd_token->body = cmd_arg_stack_to_array((t_cmd_arg *) cmd_token->body);
	cmd_arg_clear(arg_stack);
	cmd_token->body_type = ARRRAY;
	if (errno)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Replace env var in each argument of a command
 */
static int	replace_cmd_arg(t_hashtable *envp_dict, t_cmd_arg *args)
{
	t_cmd_arg	*tmp;

	while (args)
	{
		args->arg = replace_env(envp_dict, args->arg);
		if (errno)
			return (FAILURE);
		tmp = args;
		args = split_arg(args);
		if (errno)
			return (FAILURE);
		args = replace_split_wildcard(tmp, args);
		if (errno)
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Replace env var in a redirect
 * @return
 * Return FAILURE if an error occurred or if the filename is ambiguous
 * Return SUCCESS otherwise
 */
static int	replace_redirect(t_hashtable *envp_dict,
				t_cmd_token *redirect_token)
{
	t_redirect_param	*param;

	param = (t_redirect_param *) redirect_token->body;
	param->body = replace_env(envp_dict, param->body);
	param->body = wildcard_replace(param->body);
	if (param->body == NULL)
	{
		perror("minishell");
		return (return_errno_error());
	}
	if (is_ambiguous_redirect(param->body) == 1)
		return (FAILURE);
	return (SUCCESS);
}

static bool	is_ambiguous_redirect(char *file_name)
{
	size_t	index;

	index = 0;
	if (*file_name == '\0')
	{
		ft_putstr_fd("minishell: `(null)': ambiguous redirect\n", STDERR_FILENO);
		return (true);
	}
	while (file_name[index])
	{
		if (file_name[index] == '"' || file_name[index] == '\'')
			line_skip_quote(file_name, &index);
		if (ft_isspace(file_name[index]))
		{
			ft_putstr_fd("minishell: `", STDERR_FILENO);
			ft_putstr_fd(file_name, STDERR_FILENO);
			ft_putstr_fd("': ambiguous redirect\n", STDERR_FILENO);
			return (true);
		}
		index++;
	}
	return (false);
}
