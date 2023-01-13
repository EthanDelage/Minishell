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

int	main(int argc, char **argv, char **envp)
{
	t_hashtable	*envp_dict;

	(void) argc;
	(void) argv;
	envp_dict = envp_to_dict(envp);
	if (envp_dict == NULL)
		return (errno);
	hashtable_display(envp_dict);
	return (0);
}
