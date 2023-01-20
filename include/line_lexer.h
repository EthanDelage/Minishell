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

# include "token.h"

t_token	*line_lexer(char *line);
void	cmd_lexer(t_token *token);

#endif