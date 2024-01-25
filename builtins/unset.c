#include "minishell.h"

t_env	*ft_is_env(t_env *env, char *val, int i)
{
	if (i == 0)
		while (val && val[i] && val[i] != '=')
			i++;
	while (env && val)
	{
		if (env->str && !ft_strncmp(env->str, val, i))
		{
			if (env->str[i] == '=')
				return (env);
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_unset_env(t_env **env, t_env *env_to_unset)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == env_to_unset)
	{
		*env = (*env)->next;
		free(env_to_unset->str);
		free(env_to_unset);
		return ;
	}
	while (tmp->next != env_to_unset)
		tmp = tmp->next;
	tmp->next = env_to_unset->next;
	free(env_to_unset->str);
	free(env_to_unset);
}

void	ft_unset_p(t_pipex *list, t_tokens *toks, int i)
{
	t_env	*env;
	int		shlvl;

	env = list->data->env;
	toks = toks->next;
	g_minishell = 0;
	if (!toks || toks->ind_command != i)
		return ;
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	if (!toks || toks->ind_command != i)
		return ;
	env = ft_is_env(env, toks->val, ft_strlen(toks->val));
	shlvl = ft_strncmp(toks->val, "SHLVL", 5);
	if (ft_strlen(toks->val) == 6
		&& !ft_strncmp(toks->val, "OLDPWD", 6))
		list->data->old_pwd = 0;
	if (ft_strlen(toks->val) != 5)
		shlvl = 1;
	if (env)
		ft_unset_env(&(list->data->env), env);
	if (!shlvl)
		ft_shlvl(&(list->data->env));
}
