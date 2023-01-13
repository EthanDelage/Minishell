/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:57:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/12 22:57:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENVP_H
# define ENVP_H

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"

# define SIZE_HASHMAP	150

typedef struct s_dict
{
	char			*name;
	char			*value;
	struct s_dict	*next;
}				t_dict;

/* ----------	HASHMAP FUNCTIONS	---------- */

size_t	get_key(char *name);
t_dict	**init_hashmap(void);
void	display_hashmap(t_dict **hashmap);
void	hash_elem(t_dict **list, t_dict *new);

/* ----------	DICT_UTILS FUNCTIONS	---------- */

t_dict	*dict_new(char *name, char *value);
void	dict_add_back(t_dict **start, t_dict *new);
t_dict	*remove_one(t_dict **node);
void	clear_dict(t_dict **start);

/* ----------	DICT FUNCTIONS	---------- */

t_dict	**parse_envp(char **envp);
void	free_dict(t_dict **dict);

t_dict	*conv_envp_to_dict(char **envp);

#endif
