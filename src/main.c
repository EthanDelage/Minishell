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

static void	minishell_run(t_hashtable *envp_dict, struct termios term_save);
static void	minishell_exit(t_hashtable *envp_dict, char *line,
				t_token *token_stack);
static void	set_return_value(char *line);
static int	run_here_doc(t_token *line_token, struct termios term_save);

int	main(int argc, char **argv, char **envp)
{
	t_hashtable		*envp_dict;
	struct termios	term_save;

	(void) argc;
	(void) argv;
	if (termios_save(&term_save) == FAILURE)
		minishell_exit(NULL, NULL, NULL);
	envp_dict = envp_to_dict(envp);
	if (errno)
		minishell_exit(NULL, NULL, NULL);
	if (shlvl_increment(envp_dict) == FAILURE)
		minishell_exit(envp_dict, NULL, NULL);
	while (1)
		minishell_run(envp_dict, term_save);
}

static void	minishell_run(t_hashtable *envp_dict, struct termios term_save)
{
	int				ret;
	char			*line;
	t_token			*line_token;

	if (init_sigaction(sig_handler_prompt) == FAILURE)
		minishell_exit(envp_dict, NULL, NULL);
	if (pwd_set(envp_dict) == EXIT_FAILURE)
		minishell_exit(envp_dict, NULL, NULL);
	if (termios_disable_vquit() == FAILURE)
		minishell_exit(envp_dict, NULL, NULL);
	line = readline("minishell: > ");
	errno = 0;
	if (termios_restore(term_save) == FAILURE)
		minishell_exit(envp_dict, NULL, NULL);
	if (line == NULL)
		builtin_exit(envp_dict, NULL, NULL);
	add_history(line);
	line_token = analyser(line);
	if (line_token == NULL)
		return (set_return_value(line));
	free(line);
	ret = run_here_doc(line_token, term_save);
	if (ret == FAILURE)
		minishell_exit(envp_dict, NULL, line_token);
	else if (ret == -1)
	{
		token_clear(line_token);
		return ;
	}
	exec(&line_token, envp_dict);
	if (errno)
		minishell_exit(envp_dict, NULL, line_token);
	token_clear(line_token);
}

static int	run_here_doc(t_token *line_token, struct termios term_save)
{
	int	ret;

	if (termios_disable_vquit() == FAILURE)
		return (FAILURE);
	if (init_sigaction(sig_handler_here_doc) == FAILURE)
	{
		termios_restore(term_save);
		return (FAILURE);
	}
	ret = here_doc_get(line_token);
	if (ret != 0)
	{
		termios_restore(term_save);
		return (ret);
	}
	return (termios_restore(term_save));
}

static void	minishell_exit(t_hashtable *envp_dict, char *line,
				t_token *token_stack)
{
	if (envp_dict)
		hashtable_clear(envp_dict);
	if (line)
		free(line);
	if (token_stack)
		token_clear(token_stack);
	perror("minishell");
	exit(errno);
}

static void	set_return_value(char *line)
{
	if (*line == '\0')
		g_return_value = 0;
	else
		g_return_value = 2;
	free(line);
}
