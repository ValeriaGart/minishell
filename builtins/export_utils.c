/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:10:12 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 13:59:36 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_check_export_err(int type, t_pipex *list)
{
	if (type == EMPTY_STR)
	{
		ft_putstr_fd("minishell: export: `': not a valid identifier\n", 2);
		list->data->exit_code = 1;
		return (1);
	}
	return (0);
}

int	ft_add_to_env(t_env **env, char *val)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	new = ft_is_env(*env, val, 0);
	if (new)
		ft_repoint_env(tmp, &new);
	if (!new)
		new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->str = ft_strdup(val);
	if (!(new->str))
	{
		if (new != tmp)
			free(new);
		return (1);
	}
	if (tmp != new)
		new->next = *env;
	*env = new;
	return (0);
}

void	ft_loop_export(t_pipex *list, t_tokens *toks, int i, int err)
{
	if (!ft_check_export_err(toks->type, list))
	{
		if (ft_check_before_equal(toks->val))
		{
			ft_export_error(toks, toks->val, i, list);
			return ;
		}
		err = ft_check_after_equal(list->data->env, toks->val);
		if (!ft_last_pipe(toks, i))
			return ;
		if (!err && !ft_strncmp(toks->val, "SHLVL=", 6))
			ft_export_shlvl(&(list->data->env), toks->val);
		else if (!err)
		{
			if (!ft_strncmp(toks->val, "OLDPWD=", 7))
				list->data->old_pwd = 1;
			ft_add_to_env(&(list->data->env), toks->val);
		}
	}
	toks = toks->next;
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	if (toks && toks->ind_command == i)
		ft_loop_export(list, toks, i, 0);
}

int	ft_export(t_pipex *list, t_tokens *toks, int i, t_env *env)
{
	toks = toks->next;
	if (!toks || toks->ind_command != i)
		return (ft_print_env_declare_x(env, list));
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	if (!toks || toks->ind_command != i)
		return (ft_print_env_declare_x(env, list));
	ft_loop_export(list, toks, i, 0);
	return (0);
}
