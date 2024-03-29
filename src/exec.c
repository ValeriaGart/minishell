/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynguyen <ynguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:12:30 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 19:50:44 by ynguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_loop_children(t_pipex *list, int *i)
{
	ft_free_command(list->valid_env);
	ft_list_loop_free(list, *i, 0);
	list->tokens = ft_free_toks(list->tokens);
	ft_list_free(list);
	rl_clear_history();
	ft_free_env(list->data->env, list->data);
}

void ft_loop_children(t_pipex *list, int i)
{
	sig_handel(2, list->data);
	ft_check_kid(i, list);
	list->valid_env = ft_env_to_twod_arr(list->data->env);
	if (!list->valid_env || !ft_command_check(list, list->tokens, i))
	{
		if (list->here_doc)
			unlink(".heredoc");
		free_loop_children(list, &i);
		exit(list->data->exit_code);
	}
	execve(list->command, list->args, list->valid_env);
	ft_error_msg("Execve failed\n", 15);
	if (list->here_doc)
		unlink(".heredoc");
	free_loop_children(list, &i);
	exit(127);
}

void ft_exec_right_way(t_pipex **list, int err, int *i)
{
	if (!err)
	{
		if (!is_builtin((*list)->tokens, *i))
		{
			if ((*list)->ac == 1)
				(*list)->pids[*i] = fork();
			if ((*list)->pids[*i] == 0)
				ft_loop_children((*list), *i);
		}
		else if ((*list)->ac == 1 || (*list)->pids[*i] == 0)
			ft_builtins_p((*list), *i, (*list)->tokens);
	}
	else
	{
		if ((*list)->pids[*i] == 0)
			ft_free_exit_builtin(*list, *i);
	}
}

int ft_do_all_to_exec(t_pipex *list, int err, int i)
{
	while (++i < list->ac)
	{
		allocate_sig(&list, &i);
		err = ft_init_list_loop(list, i, 0);
		if (err == -2)
			return (0);
		if (err > 0)
			return (1);
		if (list->ac != 1)
		{
			if (pipe(list->pipes) == -1)
				return (ft_list_loop_free(list, i, 1), 1);
			list->pids[i] = fork();
		}
		ft_exec_right_way(&list, err, &i);
		signal(SIGINT, SIG_IGN);
		ft_list_loop_free(list, i, 0);
	}
	ft_wait_for_my_babies(list, 0);
	return (0);
}

int ft_exec(t_data *data, t_tokens *toks)
{
	t_pipex list;
	int ret;

	ret = 0;
	ret = init_malloc_pipex(&list, data, toks);
	if (!ret)
		ret = ft_do_all_to_exec(&list, 0, -1);
	list.tokens = ft_free_toks(list.tokens);
	if (ret == -5)
		return (-1);
	ft_list_free(&list);
	return (ret * -1);
}
