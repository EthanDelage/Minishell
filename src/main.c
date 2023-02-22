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
#include "exec.h"
#include "mini_signal.h"

unsigned char	g_return_value = 0;

static int	minishell_run(t_hashtable *envp_dict, struct termios term_save);
static int	minishell_exit(t_hashtable *envp_dict, char *line,
				t_token *token_stack, int return_value);

int	main(int argc, char **argv, char **envp)
{
	t_hashtable		*envp_dict;
	struct termios	term_save;
	int				exit_status;

	(void) argc;
	(void) argv;
	if (init_sigaction() == FAILURE || termios_save(&term_save) == FAILURE)
		return (minishell_exit(NULL, NULL, NULL, errno));
	envp_dict = envp_to_dict(envp);
	if (errno)
		return (minishell_exit(NULL, NULL, NULL, errno));
	if (shlvl_increment(envp_dict) == EXIT_FAILURE)
		return (minishell_exit(envp_dict, NULL, NULL, errno));
	while (1)
	{
		exit_status = minishell_run(envp_dict, term_save);
		if (exit_status != SUCCESS)
			return (exit_status);
	}
}

static int	minishell_run(t_hashtable *envp_dict, struct termios term_save)
{
	char			*line;
	t_token			*line_token;

	if (pwd_set(envp_dict) == EXIT_FAILURE)
		return (minishell_exit(envp_dict, NULL, NULL, errno));
	if (termios_disable_vquit() == FAILURE)
		return (minishell_exit(envp_dict, NULL, NULL, errno));
	line = readline("minishell: > ");
	errno = 0;
	if (line == NULL)
		builtin_exit(envp_dict, NULL, NULL);
	if (termios_restore(term_save) == FAILURE)
		return (minishell_exit(envp_dict, NULL, NULL, errno));
	add_history(line);
	line_token = analyser(line);
	if (line_token == NULL)
		return (2);
	if (here_doc_get(line_token) == FAILURE)
		return (minishell_exit(envp_dict, line, line_token, errno));
	if (termios_restore(term_save) == FAILURE)
		return (minishell_exit(envp_dict, line, line_token, errno));
	exec(&line_token, envp_dict);
	if (errno)
		return (minishell_exit(envp_dict, line, line_token, errno));
	free(line);
	token_clear(line_token);
	return (SUCCESS);
}

static int	minishell_exit(t_hashtable *envp_dict, char *line,
				t_token *token_stack, int return_value)
{
	if (envp_dict)
		hashtable_clear(envp_dict);
	if (line)
		free(line);
	if (token_stack)
		token_clear(token_stack);
	perror("minishell");
	return (return_value);
}
