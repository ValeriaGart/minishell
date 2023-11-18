/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:40:04 by vharkush          #+#    #+#             */
/*   Updated: 2023/11/17 15:46:30 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_print_env_declare_x(t_env *env, int out)
{
	if (out == -1)
		out = 1;
	while (env->next != NULL)
	{
		write(out, "declare -x ", 11);
		ft_putendl_fd(env->str, out);
		env = env->next;
	}
	return (0);
}

int	ft_env(t_data *data, t_pipex *list)
{
	t_env	*env;
	int		out;

	out = list->redir_out;
	if (out == -1)
		out = 1;
	if (ft_count_words(list->args) != 1)
		return (-2);
	env = data->env;
	while (env->next != NULL)
	{
		ft_putendl_fd(env->str, out);
		env = env->next;
	}
	return (0);
}
