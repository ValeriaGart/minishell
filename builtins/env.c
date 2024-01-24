#include "../incl/minishell.h"

t_env *ft_find_first_cur(t_env *cur)
{
	t_env	*check;

	check = cur;
	while (check && check->str)
	{
		if (ft_strcmp(cur->str, check->str) > 0)
			cur = check;
		check = check->next;
	}
	return (cur);
}

t_env	*ft_new_cur(t_env *cur, t_env *env)
{
	t_env	*next;
	t_env	*check;

	check = env;
	next = env;
	while (next && next->str && next->next && ft_strcmp(next->str, cur->str) <= 0)
		next = next->next;
	if (!next)
		return (NULL);
	while (check && check->str)
	{
		if (ft_strcmp(check->str, next->str) < 0 && ft_strcmp(check->str, cur->str) > 0)
			next = check;
		check = check->next;
	}
	cur = next;
	return (cur);
}

int	ft_print_env_declare_x(t_env *env, t_pipex *list)
{
	t_env	*cur;
	int		i;
	int		equal;

	cur = ft_find_first_cur(env);
	i = -1;
	equal = 0;
	while (cur != NULL && cur->str)
	{
		equal = 0;
		if (i != -1)
			cur = ft_new_cur(cur, env);
		i = 0;
		while (cur && cur->str && cur->str[i] && cur->str[0] != '_')
		{
			if (i == 0)
				write(list->out, "export ", 7);
			write(list->out, &(cur->str[i]), 1);
			if (cur->str[i] == '=' && equal == 0 && ++equal)
				write(list->out, "\"", 1);
			i++;
		}
		if (cur  && cur->str && cur->str[0] != '_')
			write(list->out, "\"\n", 2);
	}
	return (0);
}

int	ft_env(t_data *data, t_pipex *list, int i)
{
	t_env	*env;
	int		out;

	out = list->out;
	if (!ft_is_env(data->env, "PATH", 4))
	{
		ft_error("env", ": No such file or directory\n", 0);
		return (127);
	}
	if (ft_too_many_args(list->tokens, i, 1, "env") == NULL)
		return (127);
	env = data->env;
	while (env->next != NULL)
	{
		ft_putendl_fd(env->str, out);
		env = env->next;
	}
	return (0);
}
