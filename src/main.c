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
#include "router.h"

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);
int		exec_pipe(t_token *head, t_hashtable *envp_dict, int fd_stdin, int fd_stdout);

int	g_return_value = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*line_token;
	t_token		*tmp;
	t_hashtable	*envp_dict;

	(void) argc;
	(void) argv;
	envp_dict = envp_to_dict(envp);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (errno);
		errno = 0;
		line_token = line_lexer(line);
		if (errno)
			return (errno);
		if (error_syntax(line_parser(line_token)) == FAILURE)
			return (FAILURE);
		tmp = line_token;
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
		exec_pipe(line_token, envp_dict, STDIN_FILENO, STDOUT_FILENO);
		free(line);
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
