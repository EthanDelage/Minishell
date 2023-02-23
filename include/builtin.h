/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:09:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/16 10:09:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILTIN_H
# define BUILTIN_H

# include "envp.h"
# include "token.h"
# include "minishell.h"

/* ----------	BUILTIN FUNCTIONS	---------- */

int		builtin_pwd(void);
int		builtin_cd(t_hashtable *envp_dict, char **args);
int		builtin_env(t_hashtable *envp_dict, char **args);
int		builtin_unset(t_hashtable *envp_dict, char **args);
int		builtin_export(t_hashtable *envp_dict, char **args);
int		builtin_exit(t_hashtable *envp_dict, t_token *token_stack, char **args);
int		builtin_echo(char **args);

/* ----------	BUILTIN UTILS	---------- */

int		valid_char(char c);
int		return_errno_error(void);
void	builtin_print_error(char *name, char *arg);

#endif
