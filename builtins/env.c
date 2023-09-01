/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:40:04 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/29 14:06:13 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_env(t_data *data)
{
	t_env	*temp;

	temp = data->env;
	while (temp)
	{
		printf(".\n.\n.\n.\n.\n");
		ft_putendl_fd(temp->str, data->out);
		temp = temp->next;
	}
	printf("hi1\n");
	return (1);
}
