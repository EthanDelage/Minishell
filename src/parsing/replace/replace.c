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
#include "cmd_token.h"
#include "token.h"
#include "replace.h"
#include "envp.h"
#include "redirect.h"

static int			replace_cmd(t_hashtable *envp_dict, t_cmd_token *cmd_token);
static int			replace_redirect(t_hashtable *envp_dict,
						t_cmd_token *redirect_token);
static int			is_ambiguous_redirect(char *file_name);
static t_cmd_arg	*replace_split_wildcard(t_cmd_arg *head, t_cmd_arg *delimiter);

int	replace(t_hashtable *envp_dict, t_cmd_token *head)
{
	t_cmd_token	*token;

	token = head;
	while (token)
	{
		if (token->type == COMMAND)
		{
			if (replace_cmd(envp_dict, token) == 1)
				return (1);
		}
		else if (token->type != HERE_DOC)
		{
			if (replace_redirect(envp_dict, token) == 1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

static int	replace_cmd(t_hashtable *envp_dict, t_cmd_token *cmd_token)
{
	t_cmd_arg	*args;
	t_cmd_arg	*tmp;

	args = (t_cmd_arg *) cmd_token->body;
	while (args)
	{
		args->arg = replace_env(envp_dict, args->arg);
		if (errno)
			return (1);
		tmp = args;
		args = split_arg(args);
		if (errno)
			return (1);
		args = replace_split_wildcard(tmp, args);
		if (errno)
			return (1);
	}
	if (cmd_arg_remove_quote((t_cmd_arg *) cmd_token->body) == EXIT_FAILURE)
		return (1);
	cmd_arg_reverse((t_cmd_arg **) &cmd_token->body);
	free(cmd_token->head);
	cmd_token->head = ft_strdup(((char **) cmd_token->body)[0]);
	cmd_token->body = cmd_arg_stack_to_array((t_cmd_arg *) cmd_token->body);
	cmd_token->body_type = ARRRAY;
	if (errno)
		return (1);
	return (0);
}

static t_cmd_arg	*replace_split_wildcard(t_cmd_arg *head, t_cmd_arg *delimiter)
{
	while (head && head != delimiter)
	{
		head->arg = wildcard_replace(head->arg);
		if (errno)
			return (NULL);
		head = split_arg(head);
		if (errno)
			return (NULL);
	}
	return (head);
}

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
		return (1);
	return (0);
}

static int	is_ambiguous_redirect(char *file_name)
{
	size_t	index;

	index = 0;
	while (file_name[index])
	{
		if (file_name[index] == '"' || file_name[index] == '\'')
			line_skip_quote(file_name, &index);
		if (ft_isspace(file_name[index]))
		{
			ft_putstr_fd("minishell: `", STDERR_FILENO);
			ft_putstr_fd(file_name, STDERR_FILENO);
			ft_putstr_fd("': ambiguous redirect\n", STDERR_FILENO);
			return (1);
		}
		index++;
	}
	return (0);
}
