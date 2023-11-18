#include "minishell.h"

t_env		*ft_is_env(t_env *env, char *val, int i)
{
	if (i == 0)
		while(val && val[i] != '=')
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

	env = list->data->env;
	toks = toks->next;
	if (!toks || toks->ind_command != i)
		return ;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (!toks || toks->ind_command != i)
		return ;
	env = ft_is_env(env, toks->val, ft_strlen(toks->val));
	if (env)
		ft_unset_env(&(list->data->env), env);
}
