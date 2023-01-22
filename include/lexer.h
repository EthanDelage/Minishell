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
#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "cmd_token.h"

t_token	*line_lexer(char *line);
void	cmd_lexer(t_token *token);

#endif