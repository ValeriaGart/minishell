/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:13 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:14:14 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirout_no_com(t_tokens *toks, int i, t_pipex *list, int err)
{
	if (err)
		return (err);
	while (toks && toks->ind_command != i)
		toks = toks->next;
	while (toks && toks->ind_command == i && toks->type == SEP)
		toks = toks->next;
	if (!toks && list->redir_out != -1)
		return (-2);
	if (!toks)
		return (-2);
	return (0);
}

int	ft_is_echo_last(t_tokens *toks, int i)
{
	t_tokens	*if_last;

	if_last = toks;
	if_last = if_last->next;
	while (if_last && if_last->type == SEP)
		if_last = if_last->next;
	if (!if_last || if_last->ind_command != i)
		return (0);
	if (toks)
		toks = toks->prev;
	while (toks && toks->prev && toks->type != COM)
		toks = toks->prev;
	if (toks && !ft_strncmp(toks->val, "echo", 4) && ft_strlen(toks->val) == 4)
		return (1);
	return (0);
}

void	ft_change_args(t_tokens **toks)
{
	t_tokens	*prev;
	t_tokens	*next;

	if (!*toks)
		return ;
	next = (*toks)->next;
	prev = (*toks)->prev;
	if ((*toks)->val)
		free((*toks)->val);
	free(*toks);
	if (next)
		next->prev = prev;
	if (prev)
	{
		prev->next = next;
		*toks = prev;
		return ;
	}
	*toks = next;
}

void	count_and_swap(t_tokens	**iter, int *i)
{
	while ((*iter)->ind_command != (*i))
		(*iter) = (*iter)->next;
	while ((*iter) && (*iter)->ind_command == (*i))
		ft_change_args(iter);
	while ((*iter) && (*iter)->prev)
		(*iter) = (*iter)->prev;
}

void	ft_del_com(t_pipex **list, t_tokens **tokens, int i, int completely)
{
	t_tokens	*iter;

	iter = *tokens;
	if (completely)
	{
		count_and_swap(&iter, &i);
		*tokens = iter;
		if (iter == NULL)
			(*list)->tokens = iter;
		return ;
	}
	if (iter->prev->type == SEP)
		++i;
	while (--i)
		ft_change_args(&iter);
	if (!iter)
		(*list)->tokens = NULL;
	if (iter && iter->prev == NULL)
		(*list)->tokens = iter;
	if (iter)
	{
		(*list)->block_incr_redir = 1;
		*tokens = iter;
	}
}
