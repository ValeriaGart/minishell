/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:40:04 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/29 18:23:55 by yenng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data data)
{
	t_env	*temp;

	temp = data.env;
	while (temp)
	{
		ft_putendl_fd(temp->str, data.out);
		temp = temp->next;
	}
}
