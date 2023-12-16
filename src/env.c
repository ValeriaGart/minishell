#include "../incl/minishell.h"

/* Needed to check OLDPWD in env and leave it as it is or delete at all as bash does*/
void	ft_oldpwd_env_check(t_data *data, t_env **env)
{
	t_env	*old_pwd;
	t_env	*env_point;
	char	*oldpwd_str;
	DIR 	*dir;

	env_point = *env;
	data->old_pwd = 1;
	old_pwd = ft_is_env(*env, "OLDPWD=", 0);
	if (!old_pwd)
		return ;
	oldpwd_str = old_pwd->str + 7;
	if ((dir = opendir(oldpwd_str)) == NULL)
		ft_repoint_env(env_point, &old_pwd);
	closedir(dir);
}

/*	Needed to preset PWD in env as bash does
	Just preset correct current pwd
	add_env is for clearing if to add it to env or not*/
int	ft_pwd_env_check(t_data *data, t_env **env, int add_env)
{
	char	*pwd_str;
	char 	*val;
	char	*tmp;

	tmp = ft_calloc(sizeof(char), 10000);
	if (tmp == NULL)
		return (1);
	pwd_str = getcwd(tmp, 9999);
	if (pwd_str == NULL)
	{
		free(tmp);
		return (2);
	}
	val = ft_strjoin("PWD=", pwd_str);
	free (pwd_str);
	data->pwd = val;
	if (!val)
		return (3);
	if (add_env && ft_add_to_env(env, val))
		return (4);
	return (0);
}

int	ft_free_env(t_env *env, t_data *data)
{
	t_env	*head;

	head = env;
	if (data->pwd)
		free(data->pwd);
	data->pwd = NULL;
	if (!env)
		return (1);
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
	t_env *env;
	int i;

	i = -1;
	env = malloc(sizeof(t_env));
	data->env = env;
	if (!env)
		return (1);
	env->next = NULL;
	env->str = NULL;
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
	if (ft_store_env(data, env))
		return (ft_free_env(data->env, data));
	if (ft_pwd_env_check(data, &(data->env), 1))
		return (ft_free_env(data->env, data));
	ft_oldpwd_env_check(data, &(data->env));
	if (ft_shlvl(&(data->env)))
		return (ft_free_env(data->env, data));
	return (0);
}
