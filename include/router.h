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

# include "builtin.h"
# include "token.h"
# include "envp.h"
# include "libft.h"
# include "mini_signal.h"
# include <fcntl.h>

int		cmd_router(t_token *token, t_hashtable *envp_dict);
int		exec_path(t_cmd_token *cmd_token, t_hashtable *envp_dict);
int		exec_builtin(t_token *cmd_token, t_hashtable *envp_dict);
void	exec_bin(t_cmd_token *cmd_token, t_hashtable *envp_dict);
bool	is_builtin(t_cmd_token *cmd_token);
void	print_is_dir(char *name);
char	*cmd_get_path(t_cmd_token *cmd_token, char **paths);
int		is_exec_minishell(char *path);

#endif
