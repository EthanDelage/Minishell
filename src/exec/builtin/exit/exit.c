/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:52:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/27 15:52:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

int	builtin_exit(t_hashtable *envp_dict, t_token *token_stack, char **args)
{
	if (args[1] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (envp_dict)
		hashtable_clear(envp_dict);
	if (token_stack)
		token_clear(&token_stack);
	//TODO add exit value and error handling when arg is non numeric
}