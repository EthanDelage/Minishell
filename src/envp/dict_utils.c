/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:25:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/13 19:25:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

void	dict_free(t_dict **head)
{
	t_dict	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	tmp = *head;
	while (tmp != NULL)
		tmp = dict_free_elem(&tmp);
}

t_dict	*dict_free_elem(t_dict **elem)
{
	t_dict	*tmp;

	free((*elem)->name);
	if ((*elem)->value)
		free((*elem)->value);
	tmp = (*elem)->next;
	free(*elem);
	return (tmp);
}
