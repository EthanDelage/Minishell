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
	COMMAND = 0,
	REDIRECT_OUT = 1,
	REDIRECT_IN = 1,
	APPEND_OUT = 1,
	HERE_DOC = 1,
};

typedef struct s_cmd_token
{
	int					type;
	char				*head;
	void				*body;
	struct s_cmd_token	*next;
}						t_cmd_token;

#endif