/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:49:49 by vharkush          #+#    #+#             */
/*   Updated: 2023/09/01 12:23:58 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_pipex *list)
{
	char	*pwd;
	char	*tmp;

	if (ft_count_words(list->args) != 1)
		return (-3);
	tmp = malloc(sizeof(char) * 10000);
	if (tmp == NULL)
		return (-1);
	pwd = getcwd(tmp, 9999);
	if (pwd == NULL)
	{
		free (tmp);
		return (-1);
	}
	ft_putendl_fd(pwd, data->out);
	free (pwd);
	return (0);
}
