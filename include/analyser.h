/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:23:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/02/11 19:23:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef ANALYSER_H
# define ANALYSER_H

# include "lexer.h"
# include "parser.h"

t_token	*analyser(char *line);

#endif
