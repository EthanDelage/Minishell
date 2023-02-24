/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:35:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/23 08:35:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef REDIRECT_H
# define REDIRECT_H

# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include "replace.h"
# include "get_next_line.h"
# include "token.h"
# include "envp.h"
# include "mini_signal.h"
# include "minishell.h"

/* ----------	REDIRECT FUNCTIONS	---------- */

int		redirect_in_open(t_redirect_param *redirect_param);
void	redirect_in_close(t_redirect_param *redirect_param);
int		redirect_out_open(t_redirect_param *redirect_param);
void	redirect_out_close(t_redirect_param *redirect_param);
int		append_out_open(t_redirect_param *redirect_param);
void	append_out_close(t_redirect_param *redirect_param);
int		here_doc_open(t_redirect_param *param);
int		here_doc_write(t_hashtable *envp_dict,
			t_redirect_param *redirect_param);
void	here_doc_close(t_redirect_param *redirect_param);
void	here_doc_close_sigint(t_cmd_token *head, t_cmd_token *delimiter);
void	here_doc_close_error(t_redirect_param *redirect_param);
void	here_doc_close_all(t_token *head, t_token *delimiter);

/* ----------	REDIRECT_UTILS FUNCTIONS	---------- */

int		here_doc_get(t_token *head);
void	here_doc_warning(char *delimiter);
int		redirect_open(t_hashtable *envp_dict, t_cmd_token *cmd_token);
void	redirect_close(t_cmd_token *cmd_token);
void	redirect_close_unused(t_cmd_token *cmd_token, int fd_io[2]);
int		redirect_get_input_fd(t_cmd_token *head);
int		redirect_get_output_fd(t_cmd_token *head);
int		return_errno_error(void);
void	redirect_print_error(char *file_name);

#endif
