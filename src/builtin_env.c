/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:40:04 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/27 13:23:13 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
