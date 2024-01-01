#include "minishell.h"

void	ft_loop_children(t_pipex *list, int i)
{
	sig_handel(2);
	ft_check_kid(i, list);
	list->valid_env = ft_env_to_twod_arr(list->data->env);
	if (!ft_command_check(list, list->tokens, i))
	{
		if (list->here_doc)
			unlink(".heredoc");
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
	if (list->here_doc)
		unlink(".heredoc");
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
	if (g_minishell == 131)
		g_minishell = 0;
	while (i < list->ac)
	{
		if (!is_builtin(list->tokens, i))
			waitpid(list->pids[i], &status, 0);
		if (!is_builtin(list->tokens, i) && WIFEXITED(status))
			g_minishell = WEXITSTATUS(status);
		else if (!is_builtin(list->tokens, i) && WIFSIGNALED(status))
		{
			if (!g_minishell && WTERMSIG(status) == SIGINT)
			{
				g_minishell = 130;
				write(1, "\n", 1);
			}
		}
		i++;
	}
	if (list->heredoc_c)
		g_minishell = 130;
}

int	ft_do_all_to_exec(t_pipex *list, int err, int i)
{
	while (++i < list->ac)
	{
		allocate_sig(&list, &i);
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
		signal(SIGINT, SIG_IGN);
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
