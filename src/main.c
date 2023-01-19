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
#include "builtin.h"

int	main(int argc, char **argv, char **envp)
{
	t_hashtable	*envp_dict;

	(void) argc;
	(void) argv;
	envp_dict = envp_to_dict(envp);
	if (errno)
		return (errno);
	builtin_export(envp_dict, NULL);
	hashtable_clear(envp_dict);
	return (0);
}
