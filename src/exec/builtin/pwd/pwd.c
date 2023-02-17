/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:57:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/22 08:57:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "builtin.h"

/**
 * @brief Print name of current/working directory
 */
int	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (errno)
		return (return_errno_error());
	ft_putendl(buf);
	free(buf);
	return (0);
}
