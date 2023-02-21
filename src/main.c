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
#include "router.h"
#include "exec.h"
#include "mini_signal.h"

unsigned char	g_return_value = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_token			*line_token;
	t_hashtable		*envp_dict;
	struct termios	term_save;

	init_sigaction();
	if (termios_save(&term_save) < 0)
	{
		perror("minishell");
		return (1);
	}
	if (errno)
		return (errno);
	(void) argc;
	(void) argv;
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
			perror("minishell: when setting the pwd variable");
			g_return_value = errno;
			builtin_exit(envp_dict, NULL, NULL);
		}
		if (errno)
			return (errno);
		if (termios_disable_vquit() == FAILURE)
		{
			perror("minishell");
			return (1);
		}
		line = readline("minishell: > ");
		errno = 0;
		if (line == NULL)
			builtin_exit(envp_dict, NULL, NULL);
		if (termios_restore(term_save) < 0)
		{
			perror("minishell");
			return (1);
		}
		add_history(line);
		line_token = analyser(line);
		if (line_token == NULL)
			return (2);
		if (errno || here_doc_get(line_token) == FAILURE)
			return (errno);
		if (errno)
		{
			perror("");
			free(line);
			builtin_exit(envp_dict, NULL, NULL);
		}
		if (termios_restore(term_save) == FAILURE)
		{
			perror("minishell");
			return (1);
		}
		exec(&line_token, envp_dict);
		token_clear(line_token);
		free(line);
	}
}
