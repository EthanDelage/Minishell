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
	(void) argc;
	(void) argv;
	(void) envp;
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
