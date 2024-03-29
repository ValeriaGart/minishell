/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:13:45 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:13:46 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_quote(int c)
{
	if (c == D || c == S)
		return (1);
	return (0);
}

int	is_open_quote(int c)
{
	static bool	is_open[2];
	int			which_quote;

	if (c == D)
		which_quote = 0;
	else if (c == S)
		which_quote = 1;
	if (c == D || c == S)
		is_open[which_quote] ^= true;
	else
		return (0);
	return (is_open[which_quote]);
}

int	ft_is_space(char s)
{
	if (s == 32)
		return (1);
	return (0);
}

int	ft_quote_condition(char **val, int y, char *str, int *i)
{
	char	*value;
	char	meet_again;

	meet_again = str[y];
	value = *val;
	y++;
	while (str[y] != meet_again)
	{
		*i = *i + 1;
		value[*i] = str[y];
		y++;
	}
	if (ft_type_redir(value, '>', 0) == true
		|| ft_type_redir(value, '<', 0) == true)
	{
		value[*i + 2] = D;
		while (*i >= 0)
		{
			value[*i + 1] = value[*i];
			*i = *i - 1;
		}
		value[0] = D;
	}
	y++;
	return (y);
}

char	*ft_get_var_no_quote(char *buf, t_data *data, int ind)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_get_var(&buf[ind + 1], data);
	if (!str)
		return (NULL);
	if (!str[i])
		return (str);
	i++;
	while (str[i] && str[i] != D)
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i] = '\0';
	str[i - 1] = '\0';
	return (str);
}
