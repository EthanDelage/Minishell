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

t_type	cmd_token_get_type(const char *c);
char	*cmd_token_get_redirect_head(t_type	type);
char	*cmd_token_get_redirect_body(char *cmd_line, size_t *i);
void	cmd_token_add_redirect(t_token *token, t_type type, size_t *i);
void	cmd_token_add_command(t_token *token, t_cmd_arg *cmd_arg_stack);
void	cmd_token_add_cmd_arg(t_token *token, t_cmd_arg **arg_stack, size_t *i);
void	cmd_token_clear_redirect_param(t_redirect_param *param);
void	cmd_token_add(t_cmd_token **cmd_stack, t_type type, char *head,
			void *body);
void	cmd_token_reverse(t_cmd_token **head);
void	cmd_token_clear(t_cmd_token **head);

/* ---------------	CMD_ARG FUNCTIONS	--------------- */

void	cmd_arg_add(t_cmd_arg **cmd_arg_stack, char *arg);
char	**cmd_arg_stack_to_array(t_cmd_arg *cmd_arg_stack);
void	cmd_arg_clear_node(t_cmd_arg *node);
void	cmd_arg_clear(t_cmd_arg *head);
void	cmd_arg_reverse(t_cmd_arg **cmd_arg);

#endif
