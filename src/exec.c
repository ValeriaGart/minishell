#include "minishell.h"

void    ft_loop_children(t_pipex *list, int i, char **av)
{
	list->args = ft_split(av[i], ' ');
	if (!list->args)
    {
        ft_error_msg(list->data, "Malloc failed\n", 15);
        ft_list_free(list);
		close(list->pipes[0]);
		close(list->pipes[1]);
        exit(1);
    }
	ft_redirects(list, list->args);
	ft_check_kid(i, list);
//	ft_check_builtins(list);
    list->valid_env = ft_env_to_twod_arr(list->data, list->data->env);
	list->command = ft_gimme_com(list->args[0], list);
	//ft_putstr_fd(list->command, 1);
	execve(list->command, list->args, list->valid_env);
    ft_error_msg(list->data, "Execve failed\n", 15);
    ft_list_free(list);
    exit(1);
}

int    ft_do_all_to_exec(t_pipex *list, char **av)
{
	int	i;

	i = -1;
	list->rem_fd = -1;
	while (++i < list->ac)
	{
		if (i < list->ac - 1)
			pipe(list->pipes);
		list->pids[i] = fork();
        if (list->pids[i] == 0)
			ft_loop_children(list, i, av);
		if (list->rem_fd != -1)
			close(list->rem_fd);
		if (i < list->ac - 1)
			list->rem_fd = list->pipes[0];
		if (list->ac != 1)
			close(list->pipes[1]);
    }
	i = -1;
	while (++i < list->ac)
		wait(NULL);
    return (0);
}

int	ft_exec(int ac, char **av, t_data *data)
{
    t_pipex	list;

	list.data = data;
	list.here_doc = -1;
    list.paths = ft_bcheck_paths(data, data->env);
    if (!list.paths)
        return (1);
    list.com_paths = ft_split(list.paths, ':');
    if (!list.com_paths)
        return (ft_error_msg(data, "Malloc failed\n", 15));
    list.ac = ac;
    list.pids = malloc(list.ac * sizeof(pid_t));
    if (!list.pids)
    {
        free(list.com_paths);
        return (ft_error_msg(data, "Malloc failed\n", 15));
    }
    list.redir_in = -1;
    list.redir_out = -1;
    ft_do_all_to_exec(&list, av);
    ft_list_free(&list);
    return (data->exit_st);
}
