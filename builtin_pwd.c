/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:49:49 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/29 18:23:49 by yenng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data data)
{
	char	*pwd;
	char	*tmp;

	tmp = malloc(sizeof(char) * 10000);
	if (tmp == NULL)
		return (-1);
	pwd = getcwd(tmp, 9999);
	if (pwd == NULL)
	{
		free (tmp);
		return (-1);
	}
	ft_putendl_fd(pwd, data.out);
	free (pwd);
	return (0);
}
