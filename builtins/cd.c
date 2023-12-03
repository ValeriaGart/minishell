#include "minishell.h"

// if i == 1 -> "not set" , else -> "No such file or directory"
void	ft_error_cd(char *str, int i)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	if (i == 1)
		ft_putstr_fd(": not set\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

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

int		ft_cd_tilde(t_env *env,t_tokens *toks)
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
	return (0);
}
 
//if list->data->old_pwd - update, else don't touch
//if PWD->update it, else don't touh 
int		ft_update_pwd_env(t_pipex *list)
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

t_tokens	*ft_too_many_args(t_tokens *toks, int i, int limit, char *com)
{
	t_tokens	*ret;

	while (toks->ind_command != i)
		toks = toks->next;
	toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	ret = toks;
	limit--;
	if (toks->next)
		toks = toks->next;
	while (toks && toks->ind_command == i)
	{
		if (toks->type != SEP)
			limit--;
		if (limit)
		{
			g_minishell = 1;
			ft_error(com, ": too many arguments\n", 0);
			return (NULL);
		}
		toks = toks->next;
	}
	return (ret);
}

int		ft_cd(t_pipex *list, t_env *env, t_tokens *toks, int i)
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
