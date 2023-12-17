#include "minishell.h"

int	is_builtin(t_tokens *toks, int i)
{
	int	builtin;

	while (toks && !(toks->type == COM && toks->ind_command == i))
		toks = toks->next;
	if (!toks || toks->ind_command != i)
		return (0);
	builtin = ft_strlen(toks->val);
	if (builtin >= 3 && !ft_strncmp(toks->val, "env", 4))
		builtin = 1;
	else if (builtin >= 2 && !ft_strncmp(toks->val, "cd", 3))
		builtin = 1;
	else if (builtin >= 4 && !ft_strncmp(toks->val, "exit", 5))
		builtin = 1;
	else if (builtin >= 6 && !ft_strncmp(toks->val, "export", 7))
		builtin = 1;
	else if (builtin >= 5 && !ft_strncmp(toks->val, "unset", 6))
		builtin = 1;
	else if (builtin >= 4 && !ft_strncmp(toks->val, "echo", 5))
		builtin = 1;
	else if (builtin >= 3 && !ft_strncmp(toks->val, "pwd", 4))
		builtin = 1;
	else
		builtin = 0;
	return (builtin);
}

void	ft_builtins_p(t_pipex *list, int i, t_tokens *toks)
{
	int	builtin;

	list->out = ft_right_out(list, i);
	while (toks->ind_command != i)
		toks = toks->next;
	while (toks->type != COM)
		toks = toks->next;
	builtin = ft_strlen(toks->val);
	if (builtin >= 3 && !ft_strncmp(toks->val, "env", 4))
		g_minishell = ft_env(list->data, list, i);
	else if (builtin >= 4 && !ft_strncmp(toks->val, "exit", 5))
		ft_exit_p(list, toks, i);
	else if (builtin >= 6 && !ft_strncmp(toks->val, "export", 7))
		ft_export(list, toks, i, list->data->env);
	else if (builtin >= 5 && !ft_strncmp(toks->val, "unset", 6))
		ft_unset_p(list, toks, i);
	else if (builtin >= 3 && !ft_strncmp(toks->val, "pwd", 4))
		ft_pwd(list);
	else if (builtin >= 4 && !ft_strncmp(toks->val, "echo", 5))
		g_minishell = ft_echo(list, toks, i);
	else if (builtin >= 2 && !ft_strncmp(toks->val, "cd", 3))
		ft_cd(list, list->data->env, toks, i);
}
