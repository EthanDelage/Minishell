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
# include "cmd_token.h"

enum
{
	OPEN_PARENTHESIS = 0,
	OPERATOR = 1,
	PIPE = 2,
	CLOSE_PARENTHESIS = 3,
	COMMAND = 4
};

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_cmd_token	*cmd_start;
	struct s_token		*next;
}						t_token;

t_token	*token_new(int type, void *value);
int		token_get_type(const char *c);
void	token_add_command(t_token **token_stack, char *line, size_t *i);
void	token_add_parenthesis(t_token **token_stack, int type, size_t *i);
void	token_add_operator(t_token **token_stack, const char *line, size_t *i);
void	token_add_pipe(t_token **token_stack, size_t *i);
void	token_clear(t_token **token_stack);
void	token_reverse(t_token **token_stack);

#endif