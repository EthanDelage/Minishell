/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:36:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/01/28 18:36:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXEC_H
# define EXEC_H

# include "token.h"
# include "redirect.h"
# include "envp.h"
# include "router.h"
# include "replace.h"
# include <wait.h>

t_token	*exec_router(t_token *head, t_hashtable *envp_dict);
t_token	*exec_operator(t_token *head, t_hashtable *envp_dict);
int		exec_cmd(t_token *token, t_hashtable *envp_dict);
int		exec_pipe(t_token *token, t_hashtable *envp_dict, int fd_pipe_in);

#endif
