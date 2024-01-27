/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:09:40 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:09:41 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cdhome(t_env *env)
{
	t_env	*home_path;

	home_path = ft_is_env(env, "HOME", 4);
	if (!home_path)
	{
		g_minishell = 1;
		ft_error_cd("HOME", 1);
		return ;
	}
	if (ft_strlen(home_path->str + 5) < 1)
		write(1, "\n", 1);
	else if (chdir(home_path->str + 5) == -1)
		ft_error_cd(home_path->str + 5, 2);
}

int	ft_follow_oldpwd(t_env *env)
{
	t_env	*old_pwd;

	old_pwd = ft_is_env(env, "OLDPWD=", 0);
	if (!old_pwd)
	{
		ft_error_cd("OLDPWD", 1);
		g_minishell = 1;
		return (0);
	}
	ft_putstr_fd((old_pwd->str) + 7, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (chdir((old_pwd->str) + 7) == -1)
	{
		ft_error_cd((old_pwd->str) + 7, 2);
		return (1);
	}
	return (0);
}

int	ft_cd_tilde(t_env *env, t_tokens *toks)
{
	t_env	*home_path;
	char	*path_trim;
	char	*path;

	home_path = ft_is_env(env, "HOME", 4);
	if (!home_path)
	{
		g_minishell = 1;
		ft_error_cd("HOME", 1);
		return (0);
	}
	path_trim = ft_strtrim(toks->val, "~");
	if (!path_trim)
		return (1);
	path = ft_strjoin(home_path->str + 5, path_trim);
	free(path_trim);
	if (!path)
		return (2);
	if (chdir(path) == -1)
		ft_error_cd(path, 2);
	free(path);
	return (0);
}

int	ft_update_pwd_env(t_pipex *list)
{
	char	*old_pwd;
	t_env	*pwd;

	if (list->data->old_pwd)
	{
		old_pwd = ft_strjoin("OLDPWD=", ((list->data->pwd) + 4));
		if (!old_pwd)
			return (1);
		if (ft_add_to_env(&(list->data->env), old_pwd))
		{
			free(old_pwd);
			return (2);
		}
		free(old_pwd);
	}
	pwd = ft_is_env(list->data->env, "PWD=", 0);
	free(list->data->pwd);
	list->data->pwd = NULL;
	if (!pwd)
		ft_pwd_env_check(list->data, &(list->data->env), 0);
	else
		ft_pwd_env_check(list->data, &(list->data->env), 1);
	return (0);
}

int	ft_cd(t_pipex *list, t_env *env, t_tokens *toks, int i)
{
	g_minishell = 0;
	toks = ft_too_many_args(toks, i, 2, "cd");
	if (g_minishell)
		return (0);
	if (!toks)
		ft_cdhome(env);
	else if (toks->val[0] == '~')
	{
		if (ft_cd_tilde(env, toks))
			return (1);
	}
	else if (toks->val[0] == '-' && ft_strlen(toks->val) == 1)
	{
		if (ft_follow_oldpwd(env))
			return (1);
	}
	else
	{
		if (chdir(toks->val) == -1)
		{
			g_minishell = 1;
			ft_error_cd(toks->val, 2);
		}
	}
	return (ft_update_pwd_env(list));
}
