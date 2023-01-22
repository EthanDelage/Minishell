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

#include <readline/readline.h>
#include <readline/history.h>

char	*replace(t_hashtable *envp_dict, char *line);

int	main(int argc, char **argv, char **envp)
{
	t_hashtable	*envp_dict;
	char		*line;

	(void) argc;
	(void) argv;
	envp_dict = envp_to_dict(envp);
	if (errno)
		return (errno);
	while (1)
	{
		line = readline("> ");
		if (errno || line == NULL)
			return (1);
		add_history(line);
		errno = 0;
		printf("%s|\n", replace(envp_dict, line));
		if (errno)
			printf("error\n");
	}
	hashtable_clear(envp_dict);
	return (0);
}
