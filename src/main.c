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
#include "exec.h"

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);

unsigned char	g_return_value = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*line_token;
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
		line_token = analyser(line);
		if (line_token == NULL)
			return (1);
		if (exec_simple_cmd(line_token, envp_dict) == -1)
			return (1);
		if (exec_pipe(line_token, envp_dict, STDIN_FILENO) == -1)
			return (1);
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
