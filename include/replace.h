/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:25:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/24 08:25:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef REPLACE_H
# define REPLACE_H

# include <stdio.h>
# include <stdlib.h>
# include "envp.h"

char	*replace(t_hashtable *envp_dict, char *line);
char	*trim_quotes(char *str);
int		valid_char(char c);

#endif