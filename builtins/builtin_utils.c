/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:09:22 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 14:07:23 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_end_space(t_tokens *toks, int i)
{
	if (toks->type != SEP)
		return (0);
	toks = toks->next;
	while (toks && toks->ind_command == i)
	{
		if (toks->type == COM)
			return (0);
		toks = toks->next;
	}
	return (1);
}

bool	ft_last_pipe(t_tokens *toks, int i)
{
	while (toks && toks->next)
		toks = toks->next;
	if (toks && toks->ind_command == i)
		return (true);
	return (false);
}

t_tokens	*ft_point_to_needed_tok(t_tokens *toks, int i,
				int next, int skip_char)
{
	if (!toks)
		return (NULL);
	if (skip_char)
	{
		while (toks && toks->ind_command == i && toks->type == SEP)
			toks = toks->next;
		return (toks);
	}
	while (toks && toks->ind_command != i)
		toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (toks && next)
		toks = toks->next;
	return (toks);
}

t_tokens	*ft_too_many_args(int i, int limit, char *com, t_pipex *list)
{
	t_tokens	*ret;
	t_tokens	*toks;

	toks = list->tokens;
	toks = ft_point_to_needed_tok(toks, i, 1, 0);
	toks = ft_point_to_needed_tok(toks, i, 0, SEP);
	ret = toks;
	limit--;
	if ((!toks || toks->ind_command != i) && com[0] == 'c')
		return (NULL);
	if (!toks || toks->ind_command != i)
		return (list->tokens);
	while (toks && toks->ind_command == i)
	{
		if (toks->type != SEP)
			limit--;
		if (limit)
		{
			list->data->exit_code = 1;
			ft_error(com, ": too many arguments\n", 0);
			return (NULL);
		}
		toks = toks->next;
	}
	return (ret);
}
