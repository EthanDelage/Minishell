/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:18:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/10 11:18:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <readline/readline.h>
#include "envp.h"
#include "parser.h"
#include "lexer.h"
#include "redirect.h"
#include "replace.h"

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);
int		exec_pipe(t_token *head, t_hashtable *envp_dict, int fd_stdin, int fd_stdout);

int	g_return_value;

int	main(int argc, char **argv, char **envp)
{
	t_redirect_param	redirect_param;
	t_hashtable			*envp_dict;
	t_token				*cmd_stack;
	t_token				*tmp;
	char				*line;

	(void) argc;
	(void) argv;
	envp_dict = envp_to_dict(envp);
	if (errno)
		return (errno);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (1);
		errno = 0;
		cmd_stack = line_lexer(line);
		if (errno)
			return (errno);
		if (error_syntax(line_parser(cmd_stack)) == FAILURE)
			return (FAILURE);
		tmp = cmd_stack;
		while (tmp)
		{
			if (tmp->type == COMMAND)
			{
				cmd_lexer(tmp);
				if (errno)
					return (errno);
				if (error_syntax(cmd_parse(&tmp->cmd_stack)) == FAILURE)
					return (FAILURE);
			}
			tmp = tmp->next;
		}
		if (exec_pipe(cmd_stack, envp_dict, STDIN_FILENO, STDOUT_FILENO) == -1)
			return (1);
		free(line);
		token_clear(&cmd_stack);
	}
	hashtable_clear(envp_dict);
	return (0);
}

void	print_redirect(t_token *token)
{
	printf("REDIRECT:\n");
	printf("%s\n", token->cmd_stack->head);
	printf("%s\n", ((t_redirect_param *)token->cmd_stack->body)->body);
}

void	print_cmd_body(t_token *token)
{
	int i;
	char **body;

	i = 0;
	body = (char **) token->cmd_stack->body;
	printf("COMMAND:\nName:\n%s\n------------\n", token->cmd_stack->head);
	while (body[i])
	{
		body[i] = trim_quotes(body[i]);
		printf("%s\n", body[i]);
		i++;
	}
}
