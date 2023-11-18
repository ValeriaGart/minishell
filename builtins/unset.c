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
	//if (env)
	//	ft_unset_env();
}
