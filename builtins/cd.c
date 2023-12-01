#include "minishell.h"

// if i == 1 -> "not set" , else -> "No such file or directory"
void	ft_error_cd(char *str, int i)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	if (i == 1)
		ft_putstr_fd(": not set\n", 2);
	else
		ft_putstr_fd(": NO such file or directory\n", 2);
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
	if (ft_strlen(home_path->str) < 1)
		write(2, "\n", 1);
	else if (chdir(home_path->str) == -1)
		ft_error_cd(home_path->str + 5, 2);
}

void	ft_cd(t_env *env, t_tokens *toks, int i)
{
	t_env	*env_pwd;
	char	*pwd_path;

	while (toks->ind_command != i)
		toks = toks->next;
	toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (!toks)
		ft_cdhome(env);
	env_pwd = ft_is_env(env, "PWD", 3);
	pwd_path = env_pwd->str;
	if (!pwd_path)
		return ;
}
