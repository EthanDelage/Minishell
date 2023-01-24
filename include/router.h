/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:16:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/23 09:16:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef ROUTER_H
# define ROUTER_H

# include <wait.h>
# include "builtin.h"
# include "token.h"
# include "envp.h"
# include "libft.h"

int	cmd_router(t_cmd_token *cmd_token, t_hashtable *envp_dict);

#endif