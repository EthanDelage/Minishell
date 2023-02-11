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

# include <stdbool.h>
# include "token.h"
# include "cmd_token.h"

int		error_syntax(char *value);
int		line_parser(t_token *head);
int		cmd_parser(t_token *head);
t_token	*analyser(char *line);

#endif
