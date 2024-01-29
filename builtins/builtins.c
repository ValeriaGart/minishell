/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:09:31 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 13:05:31 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_exit_builtin(t_pipex *list, int i)
{
	ft_list_loop_free(list, i, 0);
	list->tokens = ft_free_toks(list->tokens);
	ft_list_free(list);
	rl_clear_history();
	ft_free_env(list->data->env, list->data);
	exit(g_minishell);
}

bool ft_builtin_check(char *command, int com_len, char *to_compare,
					  int to_comp_len)
{
	int plus_str;

	if (com_len >= to_comp_len)
	{
		plus_str = com_len - to_comp_len;
		if (!ft_strncmp(command + plus_str, to_compare, to_comp_len))
		{
			if (com_len == to_comp_len || (access(command, F_OK) == 0))
				return (true);
		}
	}
	return (false);
}

int is_builtin(t_tokens *toks, int i)
{
	int builtin;

	while (toks && !(toks->type == COM && toks->ind_command == i))
		toks = toks->next;
	if (!toks || toks->ind_command != i)
		return (0);
	builtin = ft_strlen(toks->val);
	if (ft_builtin_check(toks->val, builtin, "env", 3) == true)
		builtin = 1;
	else if (ft_builtin_check(toks->val, builtin, "cd", 2) == true)
		builtin = 1;
	else if (ft_builtin_check(toks->val, builtin, "exit", 4) == true)
		builtin = 1;
	else if (ft_builtin_check(toks->val, builtin, "export", 6) == true)
		builtin = 1;
	else if (ft_builtin_check(toks->val, builtin, "unset", 5) == true)
		builtin = 1;
	else if (ft_builtin_check(toks->val, builtin, "echo", 4) == true)
		builtin = 1;
	else if (ft_builtin_check(toks->val, builtin, "pwd", 3) == true)
		builtin = 1;
	else
		builtin = 0;
	return (builtin);
}

void ft_builtins_p(t_pipex *list, int i, t_tokens *toks)
{
	int builtin;

	list->out = ft_right_out(list, i);
	while (toks->ind_command != i)
		toks = toks->next;
	while (toks->type != COM)
		toks = toks->next;
	builtin = ft_strlen(toks->val);
	g_minishell = 0;
	if (list->ac == 1 && ft_builtin_check(toks->val, builtin, "exit", 4))
		ft_exit_p(list, toks, i);
	if (ft_builtin_check(toks->val, builtin, "env", 3) == true)
		g_minishell = ft_env(list->data, list, i);
	else if (ft_builtin_check(toks->val, builtin, "cd", 2) == true)
		ft_cd(list, list->data->env, toks, i);
	else if (ft_builtin_check(toks->val, builtin, "export", 6) == true)
		ft_export(list, toks, i, list->data->env);
	else if (ft_builtin_check(toks->val, builtin, "unset", 5) == true)
		ft_unset_p(list, toks, i);
	else if (ft_builtin_check(toks->val, builtin, "echo", 4) == true)
		g_minishell = ft_echo(list, toks, i);
	else if (ft_builtin_check(toks->val, builtin, "pwd", 3) == true)
		ft_pwd(list);
	if (list->ac != 1 && list->pids[i] == 0)
		ft_free_exit_builtin(list, i);
}
