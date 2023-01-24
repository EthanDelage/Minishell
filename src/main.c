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

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);

#include <readline/readline.h>
#include <readline/history.h>

char	*replace(t_hashtable *envp_dict, char *line);

int	main(int argc, char **argv, char **envp)
{
	t_redirect_param	redirect_param;
	t_hashtable			*envp_dict;

	(void) argv;
	(void) argc;
	envp_dict = envp_to_dict(envp);
	if (envp_dict == NULL)
		return (1);
	redirect_param.body = "EOF";
	here_doc_open(&redirect_param);
	printf("%s", redirect_param.body);
	here_doc_close(&redirect_param);
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
		printf("%s\n", body[i]);
		i++;
	}
}
