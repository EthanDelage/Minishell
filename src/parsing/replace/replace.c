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
#include "token.h"
#include "replace.h"
#include "envp.h"
#include "redirect.h"

static int	replace_cmd(t_hashtable *envp_dict, t_cmd_token *cmd_token);
static int	replace_redirect(t_hashtable *envp_dict, t_cmd_token *redirect_token);
static int	is_ambiguous_redirect(char *file_name);

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
		else
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
	(void) envp_dict;
	(void) cmd_token;
	return (0);
}

static int	replace_redirect(t_hashtable *envp_dict, t_cmd_token *redirect_token)
{
	t_redirect_param	*param;

	param = (t_redirect_param *) redirect_token->body;
	param->body = replace_env(envp_dict, param->body);
	printf("%s\n", param->body);
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
