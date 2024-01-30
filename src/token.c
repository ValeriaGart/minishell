/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:14:34 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 14:02:33 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_dlist	*ft_create_dlist(char *s, int quote)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->str = ft_strdup(s);
	node->quote = quote;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	ft_add_dlist_back(t_dlist **dl, char *str, int quote)
{
	t_dlist	*tmp;

	if (!*dl)
	{
		*dl = ft_create_dlist(str, quote);
		return ;
	}
	tmp = (*dl);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_create_dlist(str, quote);
	tmp->next->prev = tmp;
}

t_tokens	*ft_open_file(t_tokens *toks, t_pipex *list, int i, int out)
{
	if (out)
	{
		if (list->redir_out != -1)
			close(list->redir_out);
	}
	else
	{
		if (list->redir_in != -1)
			close(list->redir_in);
	}
	toks = ft_syntax_err_redir(toks, i, list);
	return (toks);
}

int	ft_quotecho_condition(char **val, int y, char *str, int *i)
{
	char	*value;
	char	meet_again;

	meet_again = str[y];
	value = *val;
	*i = *i + 1;
	value[*i] = str[y];
	y++;
	while (str[y] != meet_again)
	{
		*i = *i + 1;
		value[*i] = str[y];
		y++;
	}
	*i = *i + 1;
	value[*i] = str[y];
	y++;
	return (y);
}
