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
		//TODO: manage signal with here_doc
		term = termios_get(STDIN_FILENO);
		if (errno)
			return (errno);
		termios_init_rl(term);
		if (errno)
			return (errno);
		line = readline("> ");
		tcsetattr(STDIN_FILENO, 0, &term);
		if (errno || line == NULL)
			builtin_exit(envp_dict, NULL, NULL);
		add_history(line);
		line_token = analyser(line);
		if (line_token == NULL)
			return (2);
		termios_init_heredoc(term);
		if (errno || here_doc_get(line_token) == FAILURE)
			return (errno);
		tcsetattr(STDIN_FILENO, 0, &term);
		if (errno)
		{
			perror("");
			free(line);
			builtin_exit(envp_dict, NULL, NULL);
		}
		exec(line_token, envp_dict);
		token_clear(&line_token);
		free(line);
	}
}
