
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
		if (S_ISREG(buf.st_mode))
		{
       	    ft_error(toks->val, ": Permission denied", ft_strlen(toks->val));
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
/*	if (stat(list->command, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			ft_error(toks->val, ": command not found\n", 0);
		g_minishell = 127;
		return (false);
	}*/
	return (true);
}

void	ft_loop_children(t_pipex *list, int i, char **av)
{
	(void)av;
	ft_check_kid(i, list);
	ft_check_builtins(list, i, list->tokens);
	list->valid_env = ft_env_to_twod_arr(list->data->env);
	if (!ft_command_check(list, list->tokens, i))
	{
		ft_list_free(list);
		exit(g_minishell);
	}
	execve(list->command, list->args, list->valid_env);
	ft_error_msg("Execve failed\n", 15);
	ft_list_free(list);
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
 		waitpid(list->pids[i], &status, 0);
		if (WIFEXITED(status) && !list->builtin)
			g_minishell = WEXITSTATUS(status);
		i++;
	}
}

int	ft_do_all_to_exec(t_pipex *list, char **av)
{
	int	i;

	i = -1;
	list->rem_fd = -1;
	while (++i < list->ac)
	{
		list->builtin = 0;
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
		if (!is_builtin(list->tokens, i))
		{
			list->command = ft_gimme_com(list->tokens, list, i);	
			if (!list->command)
				return (1);
		}
		else
			list->builtin = 1;
		if (i < list->ac - 1)
			pipe(list->pipes);
		list->pids[i] = fork();
		if (list->pids[i] == 0)
			ft_loop_children(list, i, av);
 		ft_list_loop_free(list);
		ft_builtins_p(list, i, list->tokens);
		if (list->rem_fd != -1)
			close(list->rem_fd);
		if (i < list->ac - 1)
			list->rem_fd = list->pipes[0];
		if (list->ac != 1)
			close(list->pipes[1]);
	}
	ft_wait_for_my_babies(list);
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
