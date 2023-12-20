#include "minishell.h"

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

//TODO: check if u close all the fds' properly
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

int	ft_do_all_to_exec(t_pipex *list, int err, int i)
{
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
	ret = ft_do_all_to_exec(&list, 0, -1);
	list.tokens = ft_free_toks(list.tokens);
	ft_list_free(&list);
	return (ret * -1);
}
