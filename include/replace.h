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
# include <dirent.h>
# include <stdlib.h>
# include "envp.h"
# include "token.h"

int			replace(t_hashtable *envp_dict, t_cmd_token *head);
char		*replace_env(t_hashtable *envp_dict, char *line);
char		*replace_ret_value(char *line, size_t *index);
char		*trim_quotes(char *str);
int			valid_char(char c);

/* ----------	REPLACE_UTILS FUNCTIONS	---------- */

t_cmd_arg	*split_arg(t_cmd_arg *current);
int			cmd_arg_remove_quote(t_cmd_arg *head);

/* ----------	SPLIT_ARG_UTILS FUNCTIONS	---------- */

void		line_skip_isspace(char *line, size_t *i);
void		get_end_index(char *arg, size_t *index);
int			add_new_arg(char *arg, size_t *index, t_cmd_arg *current);
t_cmd_arg	*get_return_cmd_arg(t_cmd_arg *current, size_t nb_new_arg);

/* ---------- WILDCARDS FUNCTIONS	---------- */

char	*wildcard_replace(char *template);

/* ---------- WILDCARDS_UTILS FUNCTIONS	---------- */

char		*strjoin_space(char *s1, char *s2);
char		*wildcard_skip(char *str);
char		*error(char *template, char *result);

#endif
