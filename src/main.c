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

static void	print_line(t_token *token);
void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);
int		exec_pipe(t_token *head, t_hashtable *envp_dict, int fd_stdin, int fd_stdout);

int	g_return_value;

int	main(int argc, char **argv, char **envp)
{
	t_hashtable			*envp_dict;
	t_token				*cmd_stack;
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
		cmd_stack = analyser(line);
		print_line(cmd_stack);
		free(line);
		token_clear(&cmd_stack);
	}
}

static void	print_line(t_token *token)
{
	while (token)
	{
		if (token->type == COMMAND)
		{
			if (token->cmd_stack->type == COMMAND)
				print_cmd_body(token);
			else
				print_redirect(token);
		}
		token = token->next;
	}
}

void	print_redirect(t_token *token)
{
	printf("REDIRECT:\n");
	printf("%s\n", token->cmd_stack->head);
	printf("%s\n", ((t_redirect_param *)token->cmd_stack->body)->body);
}

void	print_cmd_body(t_token *token)
{
	int		i;
	char	**body;

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
