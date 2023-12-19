
#include "minishell.h"

bool	ft_command_check(t_pipex *list, t_tokens *toks, int i)
{
	struct stat buf;

	while (toks->ind_command != i)
		toks = toks->next;
	while (toks->type != COM)
		toks = toks->next;
	if (stat(list->command, &buf) == 0 && ft_strrchr(toks->val, '/'))
	{
		if (((buf.st_mode & S_IXUSR) == 0))
		{
       	    ft_error(toks->val, ": Permission denied\n", ft_strlen(toks->val));
			g_minishell = 126;
			return (false);
		}
		if (S_ISDIR(buf.st_mode))
		{
       	    ft_error(toks->val, ": Is a directory\n", 0);
			g_minishell = 126;
			return (false);
		}
	}
	if (access(list->command, F_OK) != 0)
	{
		if (ft_strrchr(toks->val, '/'))
			ft_error(toks->val, ": No such file or directory\n", 0);
		else
			ft_error(toks->val, ": command not found\n", 0);
		g_minishell = 127;
		return (false);
	}
	if (!list->paths_exist && !ft_strrchr(toks->val, '/'))
	{
		ft_error(toks->val, ": command not found\n", 0);
		g_minishell = 127;
		return (false);
	}
	return (true);
}

//TODO: check if u close all the fds' properly
void	ft_loop_children(t_pipex *list, int i)
{
	ft_check_kid(i, list);
	list->valid_env = ft_env_to_twod_arr(list->data->env);
	if (!ft_command_check(list, list->tokens, i))
	{
		ft_free_command(list->valid_env);
		ft_list_loop_free(list, i);
		list->tokens = ft_free_toks(list->tokens);
		ft_list_free(list);
		rl_clear_history();
		ft_free_env(list->data->env, list->data);
		exit(g_minishell);
	}
	execve(list->command, list->args, list->valid_env);
	ft_error_msg("Execve failed\n", 15);
	ft_free_command(list->valid_env);
	ft_list_loop_free(list, i);
	list->tokens = ft_free_toks(list->tokens);
	ft_list_free(list);
	rl_clear_history();
	ft_free_env(list->data->env, list->data);
	exit(127);
}

void	ft_wait_for_my_babies(t_pipex *list)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < list->ac)
	{
		if (!is_builtin(list->tokens, i))
 			waitpid(list->pids[i], &status, 0);
		if (!is_builtin(list->tokens, i) && WIFEXITED(status))
			g_minishell = WEXITSTATUS(status);
		i++;
	}
}

int	ft_do_all_to_exec(t_pipex *list)
{
	int	i;
	int err;

	i = -1;
	err = 0;
	while (++i < list->ac)
	{
		err = ft_init_list_loop(list, i, 0);
		if (err == -2)
			return (0);
		if (err > 0)
			return (1);
		if (i < list->ac - 1)
			pipe(list->pipes);
		if (!err)
		{
			if (!is_builtin(list->tokens, i))
			{
				list->pids[i] = fork();
				if (list->pids[i] == 0)
					ft_loop_children(list, i);
			}
			ft_builtins_p(list, i, list->tokens);
		}
		ft_list_loop_free(list, i);
	}
	ft_wait_for_my_babies(list);
	return (0);
}

int	ft_exec(t_data *data, t_tokens *toks)
{
	t_pipex	list;
	int		ret;

	ret = 0;
	if (init_pipex(&list, data, toks))
		return (-1);
	ret = ft_do_all_to_exec(&list);
	list.tokens = ft_free_toks(list.tokens);
	ft_list_free(&list);
	return (ret * -1);
}
