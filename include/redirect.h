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
# include "token.h"
# include "envp.h"

/* ----------	REDIRECT FUNCTIONS	---------- */

int		redirect_in_open(t_redirect_param *redirect_param);
void	redirect_in_close(t_redirect_param *redirect_param);
int		redirect_out_open(t_redirect_param *redirect_param);
void	redirect_out_close(t_redirect_param *redirect_param);
int		append_out_open(t_redirect_param *redirect_param);
void	append_out_close(t_redirect_param *redirect_param);
int		here_doc_open(t_redirect_param *param);
void	here_doc_close(t_redirect_param *redirect_param);

/* ----------	REDIRECT_UTILS FUNCTIONS	---------- */

int		return_errno_error(void);
void	redirect_print_error(char *file_name);

#endif
