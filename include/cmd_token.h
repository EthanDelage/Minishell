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


typedef struct s_cmd_token
{
	int					type;
	void				*value;
	struct s_cmd_token	*next;
}						t_cmd_token;

#endif