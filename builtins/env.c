#include "../incl/minishell.h"

int	ft_print_env_declare_x(t_env *env, int out)
{
	if (out == -1)
		out = 1;
	while (env->next != NULL)
	{
		write(out, "declare -x ", 11);
		ft_putendl_fd(env->str, out);
		env = env->next;
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
