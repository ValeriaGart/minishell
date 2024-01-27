/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:09:46 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:09:47 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_quote_nflag(int *q_n, int *q, t_tokens *toks, int *y)
{
	if (!(*q) && (toks->val[*y] == S || toks->val[*y] == D))
	{
		*q_n = 0;
		*q = toks->val[*y];
		while (toks->val[*y] == *q && *q)
		{
			(*q_n)++;
			(*y)++;
		}
		return (1);
	}
	return (0);
}

int	ft_loop_n_nflag(t_tokens *toks, int *q, int *y, int *q_n)
{
	int	is_n;

	is_n = 0;
	if (toks->val[*y] == 'n')
		is_n = 1;
	if (q && toks->val[*y] == *q)
	{
		while (toks->val[*y] == *q && (--(*q_n) != -1))
			(*y)++;
		*q = 0;
	}
	if (ft_quote_nflag(q_n, q, toks, y))
		;
	else if (toks->val[*y])
		(*y)++;
	ft_quote_nflag(q_n, q, toks, y);
	return (is_n);
}

int	ft_check_nflag_chars(t_tokens *toks, int q, int *min_finish, int *is_n)
{
	int	y;
	int	q_n;

	y = 0;
	if (toks->val[0] == S || toks->val[0] == D)
		q = toks->val[0];
	while (toks->val[y] == q && q)
		y++;
	q_n = y;
	if (toks->val[y])
	{
		if (toks->val[y] == '-' && *min_finish == 0)
			*min_finish = 1;
		y++;
		ft_quote_nflag(&q_n, &q, toks, &y);
		while ((toks->val[y] == 'n' || (toks->val[y] == q && q)) && *min_finish)
			*is_n += ft_loop_n_nflag(toks, &q, &y, &q_n);
		if (toks->val[y] && (toks->val[y] != q || *min_finish == 0))
			return (0);
	}
	return (1);
}

int	ft_is_nflag_echo(t_tokens *toks)
{
	int		min_finish;
	int		is_n;

	min_finish = 0;
	is_n = 0;
	if (toks->type != COM)
		return (0);
	while (toks->prev && (toks->prev->type == COM || toks->type == EMPTY_STR))
		toks = toks->prev;
	while (toks && (toks->type == COM || toks->type == EMPTY_STR))
	{
		if (!ft_check_nflag_chars(toks, 0, &min_finish, &is_n))
			return (0);
		toks = toks->next;
	}
	if (min_finish <= 0 || !is_n)
		return (0);
	return (1);
}

int	ft_n_flag_echo(int i, t_tokens **toks, t_pipex *list)
{
	t_tokens	*toks_start;

	toks_start = list->tokens;
	if (!ft_is_nflag_echo(*toks))
		return (0);
	toks_start = ft_point_to_needed_tok(toks_start, i, 1, 0);
	while (toks_start != *toks)
	{
		if (toks_start->type == COM && !ft_is_nflag_echo(toks_start))
			return (0);
		toks_start = toks_start->next;
	}
	list->n_flag_echo = 1;
	if ((*toks)->next && (*toks)->next->ind_command == i
		&& (*toks)->next->type == SEP)
		*toks = (*toks)->next;
	return (1);
}
