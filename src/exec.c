
#include "minishell.h"

void	ft_loop_children(t_pipex *list, int i, char **av)
{
	(void)av;
	ft_check_kid(i, list);
	ft_check_builtins(list, i, list->tokens);
	list->valid_env = ft_env_to_twod_arr(list->data->env);
	execve(list->command, list->args, list->valid_env);
	ft_error_msg("Execve failed\n", 15);
	ft_list_free(list);
	exit(127);
}

int	ft_do_all_to_exec(t_pipex *list, char **av)
{
	int	i;
	int	status;

	i = -1;
	list->rem_fd = -1;
	while (++i < list->ac)
	{
		list->here_doc = 0;
		list->redir_in = -1;
		list->redir_out = -1;
		ft_redirects(i, &(list->tokens), list);
		list->args = ft_tok_to_args(list->tokens, i);
		if (!list->args)
		{
			ft_error_msg("Malloc failed\n", 15);
			ft_list_free(list);
			close(list->pipes[0]);
			close(list->pipes[1]);
			exit(1);
		}
		if (!is_builtin(list))
		{
			list->command = ft_gimme_com(list->args[0], list);	
			if (!list->command)
				return (1);
		}
		if (i < list->ac - 1)
			pipe(list->pipes);
		list->pids[i] = fork();
		if (list->pids[i] == 0)
			ft_loop_children(list, i, av);
 		ft_list_loop_free(list);
 		waitpid(list->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_minishell = WEXITSTATUS(status);
		ft_builtins_p(list, i, list->tokens);
		if (list->rem_fd != -1)
			close(list->rem_fd);
		if (i < list->ac - 1)
			list->rem_fd = list->pipes[0];
		if (list->ac != 1)
			close(list->pipes[1]);
	}
	i = -1;
	while (++i < list->ac - 1)
		wait(NULL);
	return (0);
}

int	ft_exec(int ac, char **av, t_data *data, t_tokens *toks)
{
	t_pipex	list;

	if (init_pipex(&list, data, ac, toks))
		return (1);
	ft_do_all_to_exec(&list, av);
	ft_list_free(&list);
	return (g_minishell);
}
