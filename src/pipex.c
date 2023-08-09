/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenng <yenng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:21:59 by vharkush          #+#    #+#             */
/*   Updated: 2023/08/02 11:52:22 by yenng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_loop_children(t_pipex *list, int i, char **envp, char **av)
{
	int	j;

	j = 0;
	ft_check_child(i, list);
	if (list->here_doc)
		list->args = ft_split(av[i + 3], ' ');
	else
		list->args = ft_split(av[i + 2], ' ');
	if (list->args)
		list->command = ft_gimme_command(list->args[0], list);
	else
		list->command = NULL;
	if (list->command == NULL)
	{
		free_pipes(list->n, list, av, 0);
		write(2, "Smth is wrong with the command\n", 32);
		exit (1);
	}
	perror_bmsg(NULL, j, list, i);
	if (list->here_doc)
		unlink(".heredoc");
	execve(list->command, list->args, envp);
	return (1);
}

int	ft_do_the_magic(t_pipex *list, char **envp, char **av)
{
	int	i;

	list->pipes = ft_gimme_pipes(list, av);
	i = -1;
	while (++i < list->n)
	{
		if (pipe(list->pipes[i]) < 0)
		{
			free_pipes(list->n, list, av, 0);
			perror_bmsg("pipe", 0, list, -1);
		}
	}
	i = -1;
	while (++i < list->n)
	{
		list->pids[i] = fork();
		if (list->pids[i] < 0)
			free_pipes(list->n, list, av, 1);
		if (list->pids[i] == 0)
			return (ft_loop_children(list, i, envp, av));
	}
	return (0);
}

void	ft_here_doc(t_pipex *list, char **av)
{
	char	*buf;
	int		file;

	file = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		perror_bmsg("heredoc", 0, list, -1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(STDIN_FILENO, 0);
		if (buf == NULL)
			ft_unlink(list, av, 0);
		if (!ft_strncmp(av[2], buf, ft_strlen(av[2])))
			break ;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	get_next_line(-1, 1);
	close(file);
	list->file1 = open(".heredoc", O_RDONLY);
	if (list->file1 < 0)
		ft_unlink(list, av, 1);
}

void	ft_open_files(t_pipex *list, char **av, int ac, int file)
{
	if (file == 0)
	{
		if (!ft_strncmp("here_doc", av[1], 9))
		{
			ft_here_doc(list, av);
			return ;
		}
		list->file1 = open(av[1], O_RDONLY);
		if (list->file1 < 0)
			perror_bmsg("file1", 0, list, -1);
		return ;
	}
	if (list->here_doc)
		list->file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		list->file2 = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (list->file2 < 0)
		perror_bmsg("file2", 0, list, -1);
}

int ft_pipex(char **envp, char **av, int ac)
{
	t_pipex	list;
	pid_t	*pids;

	list.here_doc = 0;
	if (!ft_strncmp("here_doc", av[1], 9))
		list.here_doc = 1;
	ft_open_files(&list, av, ac, 0);
	ft_open_files(&list, av, ac, 1);
	list.paths = ft_bcheck_paths(envp);
	list.com_paths = ft_split(list.paths, ':');
	if (!list.com_paths)
		ft_unlink(&list, av, -1);
	list.n = ac - (3 + list.here_doc);
	pids = malloc(list.n * sizeof(pid_t));
	if (!pids)
		ft_unlink(&list, av, -2);
	list.pids = pids;
	ft_do_the_magic(&list, envp, av);
	ft_bpfree(&list, 0);
	free(pids);
	return (0);
}
