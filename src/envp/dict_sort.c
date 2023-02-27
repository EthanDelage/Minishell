/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:48:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/27 21:48:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "envp.h"

static void	swap_dict(t_dict *a, t_dict *b);

void	dict_sort_name(t_dict *head)
{
	bool	change;
	t_dict	*current;

	if (head == NULL)
		return ;
	change = 1;
	while (change)
	{
		change = 0;
		current = head;
		while (current->next)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				change = 1;
				swap_dict(current, current->next);
			}
			current = current->next;
		}
	}
}

static void	swap_dict(t_dict *a, t_dict *b)
{
	t_dict	tmp;

	tmp.name = a->name;
	tmp.value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = tmp.name;
	b->value = tmp.value;
}
