/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:04:00 by edelage           #+#    #+#             */
/*   Updated: 2023/02/10 17:04:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

static int	shlvl_init(t_hashtable *envp_dict);
static int	shlvl_update(t_dict *shlvl_node);

int	shlvl_increment(t_hashtable *envp_dict)
{
	t_dict	*shlvl_node;

	shlvl_node = hashtable_search(envp_dict, "SHLVL");
	if (shlvl_node == NULL)
		return (shlvl_init(envp_dict));
	else
		return (shlvl_update(shlvl_node));
}

static int	shlvl_init(t_hashtable *envp_dict)
{
	t_dict	*shlvl_node;

	shlvl_node = (t_dict *) malloc(sizeof(t_dict));
	if (errno)
		return (EXIT_FAILURE);
	shlvl_node->name = ft_strdup("SHLVL");
	if (errno)
	{
		free(shlvl_node);
		return (EXIT_FAILURE);
	}
	shlvl_node->value = ft_strdup("0");
	if (errno)
	{
		free(shlvl_node->name);
		free(shlvl_node);
		return (EXIT_FAILURE);
	}
	hashtable_push(envp_dict, shlvl_node);
	return (EXIT_SUCCESS);
}

static int	shlvl_update(t_dict *shlvl_node)
{
	int	shlvl_value;

	shlvl_value = ft_atoi(shlvl_node->value);
	free(shlvl_node->value);
	shlvl_node->value = ft_itoa(shlvl_value + 1);
	if (errno)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
