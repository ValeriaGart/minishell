/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/07/25 19:55:33 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_free_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (env && env->next)
	{
		while (env->next->next)
			env = env->next;
		if (env->next->str)
			free(env->next->str);
		free(env->next);
		env->next = NULL;
		env = head;
	}
	if (env)
	{
		if (env->str)
			free(env->str);
		free(env);
	}
	return (1);
}

int	ft_store_env(t_data *data, char **env_orig)
{
	t_env	*env;
	int		i;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	data->env = env;
	env->next = NULL;
	while (env_orig && env_orig[i])
	{
		env->str = ft_strdup(env_orig[i]);
		if (!env->str)
			return (1);
		env->next = malloc(sizeof(t_env));
		if (!env->next)
			return (1);
		env = env->next;
		env->next = NULL;
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char**env)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		return (0);
	data.in = 1;
	data.out = 0;
	data.err = 1;
	data.ret = 0;
	if (ft_store_env(&data, env))
		return (ft_free_env(data.env));
	ft_free_env(data.env);
	return (0);
}
