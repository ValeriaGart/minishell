/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:10:27 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:10:28 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_pipex *list)
{
	char	*pwd;
	char	*tmp;
	int		out;

	g_minishell = 0;
	out = 1;
	out = list->out;
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
