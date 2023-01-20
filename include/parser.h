/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:31:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/16 22:31:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include "token.h"

enum
{
	SUCCESS		=		0,
	FAILURE		=		1,
};

char	*line_parser(t_token *head);

#endif
