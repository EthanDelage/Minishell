/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/02/06 00:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "redirect.h"

void	here_doc_close(t_redirect_param *redirect_param)
{
	if (redirect_param->fd[READ] > 0)
		close(redirect_param->fd[READ]);
}

void	here_doc_close_error(t_redirect_param *redirect_param)
{
	here_doc_close(redirect_param);
	if (redirect_param->fd[WRITE] > 0)
		close(redirect_param->fd[WRITE]);
}

char	*here_doc_warning(char *result, char *delimiter)
{
	printf("minishell: warning: here-document delimited by "
		   "end-of-file (wanted `%s')\n", delimiter);
	return (result);
}

char	*ft_strjoin_endl(char *s1, char *s2)
{
	char	*new;
	size_t	len_s1;
	size_t	len_s2;

	len_s2 = ft_strlen(s2);
	if (s1 == NULL)
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	new = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (new == NULL)
		return (NULL);
	ft_memcpy((void *) new, (void *) s1, len_s1);
	new[len_s1] = '\n';
	ft_strlcpy(&(new[len_s1 + 1]), s2, len_s2 + 1);
	free(s1);
	return (new);
}
