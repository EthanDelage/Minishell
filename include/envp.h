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
# include <stdbool.h>
# include "libft.h"
# include "minishell.h"

# define SIZE_HASHTABLE	41

typedef struct s_dict
{
	char			*name;
	char			*value;
	struct s_dict	*next;
}				t_dict;

typedef struct s_hashtable
{
	size_t	size;
	size_t	nb_elem;
	t_dict	**dict;
	t_dict	*dict_bis;
}				t_hashtable;

enum
{
	REMOVE		=	0,
	NOT_FOUND	=	1,
};

int				pwd_set(t_hashtable *envp_dict);
int				shlvl_increment(t_hashtable *envp_dict);

/* ----------	HASHTABLE FUNCTIONS	---------- */

t_hashtable		*hashtable_init(size_t size);
void			hashtable_array_clear(char **array);
void			hashtable_clear(t_hashtable *hashtable);
void			hashtable_display(t_hashtable *hashtable);
char			*hashtable_set(t_dict *node, char *new_value);
size_t			hashtable_get_key(const char *name, size_t size);
void			hashtable_push(t_hashtable *hashtable, t_dict *elem);
char			**hashtable_get_array(t_hashtable *hashtable, bool quote);
t_dict			*hashtable_search(t_hashtable *hashtable, const char *name);
int				hashtable_remove_one(t_hashtable *hashtable, const char *name);

/* ----------	DICT_UTILS FUNCTIONS	---------- */

void			dict_free(t_dict **head);
t_dict			*dict_free_elem(t_dict *elem);
void			dict_remove_one(t_dict **head, char *name);
void			dict_add_front(t_dict **head, t_dict *new_elem);

/* ----------	DICT FUNCTIONS	---------- */

t_hashtable		*envp_to_dict(char **envp);
void			dict_sort_name(t_dict *head);
t_dict			*parse_env_var(const char *envp_line);

#endif
