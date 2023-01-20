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

/* ----------	BUILTIN FUNCTIONS	---------- */

int	builtin_env(t_hashtable *envp_dict);
int	builtin_unset(t_hashtable *envp_dict, char **args);
int	builtin_export(t_hashtable *envp_dict, char **args);

/* ----------	BUILTIN UTILS	---------- */

int	valid_char(char c);
int	builtin_export_no_args(t_hashtable *envp_dict);

#endif
