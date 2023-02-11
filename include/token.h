/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:46:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/16 19:46:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <errno.h>
# include "libft.h"

enum
{
	SUCCESS		=		0,
	FAILURE		=		1,
};

enum
{
	READ = 0,
	WRITE = 1,
};

typedef struct s_redirect_param
{
	char	*body;
	int		fd[2];
}				t_redirect_param;

typedef enum e_body_type
{
	STACK,
	ARRRAY
}	t_body_type;

typedef enum e_type
{
	OPEN_PARENTHESIS,
	OPERATOR,
	PIPE,
	CLOSE_PARENTHESIS,
	COMMAND,
	REDIRECT_OUT,
	REDIRECT_IN,
	APPEND_OUT,
	HERE_DOC
}	t_type;

typedef struct s_cmd_token
{
	t_type				type;
	char				*head;
	t_body_type			body_type;
	void				*body;
	struct s_cmd_token	*next;
}						t_cmd_token;

typedef struct s_token
{
	t_type				type;
	char				*value;
	struct s_cmd_token	*cmd_stack;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd_arg
{
	char				*arg;
	struct s_cmd_arg	*next;
}				t_cmd_arg;

t_token	*token_new(t_type type, void *value);
t_type	token_get_type(const char *c);
void	token_add_command(t_token **token_stack, char *line, size_t *i);
void	token_add_parenthesis(t_token **token_stack, t_type type, size_t *i);
void	token_add_operator(t_token **token_stack, const char *line, size_t *i);
void	token_add_pipe(t_token **token_stack, size_t *i);
void	token_clear(t_token **token_stack);
void	token_reverse(t_token **token_stack);
void	line_skip_space(char *line, size_t *i);
void	line_skip_quote(const char *line, size_t *i);

#endif
