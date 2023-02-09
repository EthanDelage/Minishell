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
#include <readline/history.h>
#include "envp.h"
#include "parser.h"
#include "lexer.h"
#include "redirect.h"
#include "replace.h"
#include "router.h"
#include "exec.h"
#include "mini_signal.h"

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);

unsigned char	g_return_value = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token			*line_token;
	t_hashtable		*envp_dict;
	struct termios	term;

	init_sigaction();
	if (errno)
		return (errno);
	(void) argc;
	(void) argv;
	envp_dict = envp_to_dict(envp);
	while (1)
	{
		term = init_termios();
		line = readline("> ");
		tcsetattr(STDIN_FILENO, 0, &term);
		if (errno)
			builtin_exit(envp_dict, NULL, NULL);
		if (line == NULL)
			builtin_exit(envp_dict, NULL, NULL);
		errno = 0;
		add_history(line);
		line_token = analyser(line);
		if (line_token == NULL)
			return (1);
		if (here_doc_get(line_token) != 0)
			return (1);
		exec_operator(line_token, envp_dict);
		token_clear(&line_token);
		free(line);
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
