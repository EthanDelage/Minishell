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

enum
{
	REDIRECT_OUT = 0,
	REDIRECT_IN = 1,
	APPEND_OUT = 2,
	HERE_DOC = 3
};

typedef struct s_cmd_args
{
	char				*arg;
	struct s_cmd_args	*next;
}				t_cmd_args;

typedef struct s_cmd_token
{
	int					type;
	char				*head;
	void				*body;
	struct s_cmd_token	*next;
}						t_cmd_token;

int		cmd_token_get_type(const char *c);
void	cmd_token_add(t_cmd_token **cmd_stack, int type, char *head, void *body);
//void	cmd_token_add_redirect(t_token *token, int type, size_t *i);
char	*cmd_token_get_redirect_head(int type);
char	*cmd_token_get_redirect_body(char *cmd_line, size_t *i);

#endif
