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
#include "lexer.h"
#include "analyser.h"
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

	(void) argc;
	(void) argv;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	envp_dict = envp_to_dict(envp);
	if (errno)
		return (errno);
	if (shlvl_increment(envp_dict) == EXIT_FAILURE)
	{
		hashtable_clear(envp_dict);
		return (errno);
	}
	while (1)
	{
		if (pwd_set(envp_dict) == EXIT_FAILURE)
		{
			hashtable_clear(envp_dict);
			return (errno);
		}
		init_prompt_sigaction();
//		TODO: create a colored prompt
		line = readline("> ");
		if (tcsetattr(STDIN_FILENO, 0, &term) == -1)
		{
			free(line);
			return (1);
		}
		init_cmd_sigaction();
		if (line == NULL)
			builtin_exit(envp_dict, NULL, NULL);
		errno = 0;
		add_history(line);
		line_token = analyser(line);
		if (line_token == NULL)
			return (2);
		if (here_doc_get(line_token) != 0)
			return (errno);
		exec(line_token, envp_dict);
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
