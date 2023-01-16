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

#include "envp.h"

/* ----------	HASHTABLE FUNCTIONS	---------- */

int	builtin_unset(t_hashtable *envp_dict, const char *name);

#endif
