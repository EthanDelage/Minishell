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
#include "envp.h"
#include "lexer.h"

#include <readline/readline.h>

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);

int	main(int argc, char **argv, char **envp)
{
	t_token *line_token;
	char 			*str;
	(void)argc;
	(void)argv;
	(void)envp;

	str = readline(">");
	errno = 0;
	line_token = line_lexer(str);
	while (line_token)
	{
		if (line_token->type == COMMAND)
			cmd_lexer(line_token);
		while (line_token->cmd_stack)
		{
			if (line_token->cmd_stack->type == COMMAND)
			{
				print_cmd_body(line_token);
			}
			else
				print_redirect(line_token);
			line_token->cmd_stack = line_token->cmd_stack->next;
		}
		line_token = line_token->next;
	}
	return (0);
}

void	print_redirect(t_token *token)
{
	printf("REDIRECT:\n");
	printf("%s\n", token->cmd_stack->head);
	printf("%s\n", (char *) token->cmd_stack->body);
}

void	print_cmd_body(t_token *token)
{
	int i;
	char **body;

	i = 0;
	body = (char **) token->cmd_stack->body;
	printf("COMMAND:\n");
	while (body[i])
	{
		printf("%s\n", body[i]);
		i++;
	}
}