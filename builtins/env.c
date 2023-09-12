/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:40:04 by vharkush          #+#    #+#             */
/*   Updated: 2023/09/01 12:15:45 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_env(t_data *data, t_pipex *list)
{
	t_env	*temp;

	if (ft_count_words(list->args) != 1)
		return (-2);
	temp = data->env;
	while (temp->next != NULL)
	{
		ft_putendl_fd(temp->str, data->out);
		temp = temp->next;
	}
	return (0);
}
