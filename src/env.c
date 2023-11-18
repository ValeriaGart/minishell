#include "../incl/minishell.h"

/*int	ft_shlvl_num(t_env *new)
{
	char	*str;
	int		i;
	int		num;

	if (!new)
		return (0);
	str = new->str;
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	num = ft_atoi(str + i);
	while (num != 0 && str[i])
	{
		if (!ft_isdigit(str[i]))
			num = 0; 
		i++;
	}
	return (num);
}

int	ft_shlvl(t_env **env)
{
	t_env	*new;
	t_env	*tmp;
	char	*num;

	tmp = *env;
	new = ft_is_env(*env, "SHLVL", 0);
	num = itoa(ft_shlvl_num(new));
	if (!num)
		return (1);
	if (new)
		ft_repoint_env(tmp, &new);
	if (!new)
		new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->str = ft_strdup("SHLVL=");
	if (!(new->str))
	{
		if (new != tmp)
			free(new);
		return (1);
	}
	if (tmp != new)
		new->next = *env;
	*env = new;
	return (0);
}*/

int	ft_free_env(t_env *env)
{
	t_env	*head;

	head = env;
	if (!env && !env->next)
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
		if (env->str && *env->str)
			free(env->str);
		// free(env);
	}
	return (1);
}

int	ft_store_env(t_data *data, char **env_orig)
{
	t_env *env;
	int i;

	i = -1;
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	data->env = env;
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
		return (ft_free_env(data->env));
//	if (ft_shlvl(&(data->env)))
//		return (ft_free_env(data->env));
	return (0);
}
