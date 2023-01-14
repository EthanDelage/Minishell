/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:04:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/13 16:04:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef LINE_LEXER_H
# define LINE_LEXER_H

# include <stdlib.h>
# include <errno.h>
# include "libft.h"

enum
{
	OPEN_PARENTHESIS = 0,
	OPERATOR = 1,
	CLOSE_PARENTHESIS = 2,
	COMMAND = 3,
};

typedef struct s_line_token
{
	int					type;
	void				*value;
	struct s_line_token	*next;
}						t_line_token;

t_line_token	*line_lexer(char *line);
int				token_get_type(const char *c);
void			token_add_command(t_line_token **token_stack, char *line, size_t *i);
void			token_add_parenthesis(t_line_token **token_stack, int type, size_t *i);
void			token_add_operator(t_line_token **token_stack, const char *line, size_t *i);
void			token_clear(t_line_token **token_stack);

#endif