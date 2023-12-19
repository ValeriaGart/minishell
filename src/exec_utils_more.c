#include "../incl/minishell.h"

//TODO: overline
char	**ft_tok_to_args(t_tokens *toks, int i)
{
	int			y;
	char		**args;
	t_tokens	*rem_tok;

	y = 0;
	while (toks->ind_command != i)
		toks = toks->next;
	rem_tok = toks;
	while (toks && toks->ind_command == i)
	{
		if (toks->type != SEP)
			++y;
		toks = toks->next;
	}
	args = ft_calloc(sizeof(char *), y + 1);
	if (!args)
		return (NULL);
	i = -1;
	while (++i < y)
	{
		while (rem_tok->type == SEP)
			rem_tok = rem_tok->next;
		args[i] = ft_strdup(rem_tok->val);
		if (!args[i])
			return (ft_free_command(args));
		rem_tok = rem_tok->next;
	}
	return (args);
}

//TODO: overline
char	**ft_env_to_twod_arr(t_env *env_list)
{
	char	**env_twod;
	int		i;
	t_env	*rem_env;

	i = -1;
	rem_env = env_list;
	while (rem_env)
	{
		rem_env = rem_env->next;
		i++;
	}
	env_twod = malloc(sizeof(char *) * (i + 1));
	if (!env_twod)
	{
		ft_error_msg("Malloc failed\n", 15);
		return (NULL);
	}
	i = -1;
	while (env_list->next)
	{
		env_twod[++i] = ft_strdup(env_list->str);
		if (!env_twod[i])
		{
			while (i >= 0)
				free(env_twod[--i]);
			free(env_twod);
			ft_error_msg("Malloc failed\n", 15);
			return (NULL);
		}
		env_list = env_list->next;
	}
	env_twod[++i] = NULL;
	return (env_twod);
}
