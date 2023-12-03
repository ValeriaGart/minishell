#include "minishell.h"

int		is_builtin(t_pipex *list)
{
	int builtin;

	builtin = ft_strlen(list->args[0]);
	if (builtin >= 3 && !ft_strncmp(list->args[0], "env", 4))
		builtin = 1;
	else if (builtin >= 2 && !ft_strncmp(list->args[0], "cd", 3))
		builtin = 1;
	else if (builtin >= 4 && !ft_strncmp(list->args[0], "exit", 5))
		builtin = 1;
	else if (builtin >= 6 && !ft_strncmp(list->args[0], "export", 7))
		builtin = 1;
	else if (builtin >= 5 && !ft_strncmp(list->args[0], "unset", 6))
		builtin = 1;
	else if (builtin >= 4 && !ft_strncmp(list->args[0], "echo", 5))
		builtin = 1;
	else if (builtin >= 3 && !ft_strncmp(list->args[0], "pwd", 4))
		builtin = 1;
	else
		builtin = 0;
	return (builtin);
}

void	ft_builtins_p(t_pipex *list, int i, t_tokens *toks)
{
	int builtin;

	while (toks->ind_command != i)
		toks = toks->next;
	while (toks->type != COM)
		toks = toks->next;
	builtin = ft_strlen(toks->val);
	if (builtin >= 4 && !ft_strncmp(toks->val, "exit", 5))
		ft_exit_p(list, toks, i);
	else if (builtin >= 6 && !ft_strncmp(toks->val, "export", 7))
		ft_export(list, toks, i);
	else if (builtin >= 5 && !ft_strncmp(toks->val, "unset", 6))
		ft_unset_p(list, toks, i);
	else if (builtin >= 3 && !ft_strncmp(toks->val, "pwd", 4))
		ft_pwd(list);
	else if (builtin >= 4 && !ft_strncmp(toks->val, "echo", 5))
		return ;
	else if (builtin >= 2 && !ft_strncmp(toks->val, "cd", 3))
		ft_cd(list, list->data->env, toks, i);
}

void	ft_print_error(int builtin, char *cmd, t_pipex *list)
/*
-1: failed malloc
-2: too many args env
-3: too many args pwd
=====================
*/
{
	printf("%s: ", cmd);
	if (builtin == -1)
		printf("malloc failed\n");
	if (builtin == -2)
		printf("'%s': No such file or directory\n", list->args[1]);
	if (builtin == -3)
		printf("too many arguments\n");
}

void	ft_check_builtins(t_pipex *list, int i, t_tokens *toks)
// builins: cd echo env exit export pwd unset
{
	int builtin;

	while (toks->ind_command != i)
		toks = toks->next;
	while (toks->type != COM)
		toks = toks->next;
	builtin = ft_strlen(toks->val);
	if (builtin >= 3 && !ft_strncmp(toks->val, "env", 4))
	{
		builtin = ft_env(list->data, list);
		exit(0);
	}
	if (builtin >= 2 && !ft_strncmp(toks->val, "cd", 3))
		exit(0);
	if (builtin >= 4 && !ft_strncmp(toks->val, "exit", 5))
		ft_exit(toks, i);
	if (builtin >= 6 && !ft_strncmp(toks->val, "export", 7))
		exit(0);
	if (builtin >= 5 && !ft_strncmp(toks->val, "unset", 6))
		exit(0);
	if (builtin >= 3 && !ft_strncmp(toks->val, "pwd", 4))
		exit(0);
	if (builtin >= 4 && !ft_strncmp(toks->val, "echo", 5))
		exit(ft_echo(list, toks, i));
/*	if (builtin < 0)
		ft_print_error(builtin, list->args[0], list);
	if (builtin <= 0)
		list->args = NULL;*/
}
