/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:59:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/10 22:59:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

static int	pwd_init(t_hashtable *envp_dict);
static int	pwd_update(t_dict *pwd_node);

int	pwd_set(t_hashtable *envp_dict)
{
	t_dict	*pwd_node;

	pwd_node = hashtable_search(envp_dict, "PWD");
	if (pwd_node == NULL)
		return (pwd_init(envp_dict));
	else
		return (pwd_update(pwd_node));
}

static int	pwd_init(t_hashtable *envp_dict)
{
	t_dict	*pwd_node;

	pwd_node = (t_dict *) malloc(sizeof(t_dict));
	if (errno)
		return (FAILURE);
	pwd_node->name = ft_strdup("PWD");
	if (errno)
	{
		free(pwd_node);
		return (FAILURE);
	}
	pwd_node->value = getcwd(NULL, 0);
	if (errno)
	{
		free(pwd_node->name);
		free(pwd_node);
		return (FAILURE);
	}
	pwd_node->next = NULL;
	hashtable_push(envp_dict, pwd_node);
	return (SUCCESS);
}

static int	pwd_update(t_dict *pwd_node)
{
	if (pwd_node->value)
		free(pwd_node->value);
	pwd_node->value = getcwd(NULL, 0);
	if (errno)
		return (FAILURE);
	return (SUCCESS);
}
