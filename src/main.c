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

void	print_cmd_body(t_token *token);
void	print_redirect(t_token *token);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*line_token;
	t_token	*tmp;

	(void) argc;
	(void) argv;
	(void) envp;
	do
	{
		line = readline("minishell > ");
		errno = 0;
		line_token = line_lexer(line);
		if (line_token == NULL)
			return (1);
		if (error_syntax(line_parser(line_token)) == FAILURE)
			break;
		tmp = line_token;
		while (tmp)
		{
			if (tmp->type != COMMAND)
			{
				printf("%s\n", tmp->value);
				printf("=========================\n");
			}
			else
			{
				cmd_lexer(tmp);
				if (error_syntax(cmd_parse(&tmp->cmd_stack)) == FAILURE)
					break;
				while (tmp->cmd_stack)
				{
					if (tmp->cmd_stack->type == COMMAND)
						print_cmd_body(tmp);
					else
						print_redirect(tmp);
					printf("=========================\n");
					tmp->cmd_stack = tmp->cmd_stack->next;
				}
			}
			tmp = tmp->next;
		}
	} while (line);
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
	printf("COMMAND:\nName:\n%s\n------------\n", token->cmd_stack->head);
	while (body[i])
	{
		printf("%s\n", body[i]);
		i++;
	}
}
