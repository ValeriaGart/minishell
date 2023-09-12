/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:31:38 by vharkush          #+#    #+#             */
/*   Updated: 2023/09/02 12:39:24 by yenng            ###   ########.fr       */
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

int	ft_store_env(t_data *data, char **env_orig, char structt)
// n - new, o - orig
{
	t_env	*env;
	int		i;

	i = -1;
	env = malloc(sizeof(t_env));
	if (structt == 'n')
		data->env = env;
	else
		data->env_orig = env;
	if (!env)
		return (1);
	env->next = NULL;
	while (env_orig && env_orig[++i])
	{
		env->str = ft_strdup(env_orig[i]);
		if (!env->str)
			return (1);
		env->next = malloc(sizeof(t_env));
		if (!env->next)
			return (1);
		env->next->str = NULL;
		env = env->next;
		env->next = NULL;
	}
	env->next = NULL;
	return (0);
}

int	ft_env_init(t_data *data, char **env)
{
	if (ft_store_env(data, env, 'n'))
		return (ft_free_env(data->env));
	if (ft_store_env(data, env, 'o'))
	{
		ft_free_env(data->env);
		return (ft_free_env(data->env_orig));
	}
	return (0);
}
