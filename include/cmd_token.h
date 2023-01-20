/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:06:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/16 20:06:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef CMD_TOKEN_H
# define CMD_TOKEN_H

# include "token.h"

int		cmd_token_get_type(const char *c);
void	cmd_token_add(t_cmd_token **cmd_stack, int type, char *head, void *body);
void	cmd_token_add_command(t_token *token, t_cmd_arg *cmd_arg_stack);
void	cmd_token_add_cmd_arg(t_token *token, t_cmd_arg *arg_stack, size_t *i);
void	cmd_arg_add(t_cmd_arg **cmd_arg_stack, char *arg);
char	**cmd_arg_stack_to_array(t_cmd_arg *cmd_arg_stack);
void	cmd_arg_reverse(t_cmd_arg **cmd_arg);
void	cmd_token_add_redirect(t_token *token, int type, size_t *i);
char	*cmd_token_get_redirect_head(int type);
char	*cmd_token_get_redirect_body(char *cmd_line, size_t *i);

#endif