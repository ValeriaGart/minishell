/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/28 12:56:19 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_loop_minishell(t_data *data)
{
}

int	main(int ac, char **av, char**env)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		return (0);
	data.in = 0;
	data.out = 1;
	data.err = 1;
	if (ft_env_init(&data, env))
		return (1);
	ft_loop_minishell(&data);
	ft_free_env(data.env);
	ft_free_env(data.env_orig);
	return (0);
}
