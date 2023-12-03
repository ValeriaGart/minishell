/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:49:49 by vharkush          #+#    #+#             */
/*   Updated: 2023/12/03 12:56:07 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_pipex *list)
{
	char	*pwd;
	char	*tmp;
	int		out;

	out = 1;
	if (list->redir_out != -1)
		out = list->redir_out;
	if (ft_count_words(list->args) != 1)
		return (3);
	tmp = ft_calloc(sizeof(char), 10000);
	if (tmp == NULL)
		return (1);
	pwd = getcwd(tmp, 9999);
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, out);
	free (pwd);
	return (0);
}
