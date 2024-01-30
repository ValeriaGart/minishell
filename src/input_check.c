/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:13:29 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/30 13:41:26 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	syntax_errors(char c, t_data *data)
{
	if (c == PIPE)
	{
		data->exit_code = 2;
		ft_putendl_fd("Pipe can only be used in a full command", 2);
	}
	else if (c == D || c == S)
	{
		data->exit_code = 2;
		ft_putendl_fd("Quotes error", 2);
	}
	return (2);
}

int	check_pipe(char *input, int y, int quote, t_data *data)
{
	int	end_str;
	int	i;

	i = 0;
	end_str = ft_strlen(input) - 1;
	while (input[i] && ft_is_space(input[i]) == 1)
		i++;
	if (input[i] == PIPE || !input[i])
		return (syntax_errors(input[i], data));
	while (end_str != 0 && ft_is_space(input[end_str]))
		end_str--;
	if (input[end_str] == PIPE)
		return (syntax_errors(input[end_str], data));
	y++;
	while (input[y] && ft_is_space(input[y]) == 1)
		y++;
	if (!quote && input[y] == PIPE)
		return (syntax_errors(input[y], data));
	return (0);
}

int	check_open_quote(char *s, t_data *data)
{
	int		i;
	char	rem;

	i = 0;
	while (s[i])
	{
		if (s[i] == S || s[i] == D)
		{
			rem = s[i];
			i++;
			while (s[i] && s[i] != rem)
				i++;
			if (s[i] == '\0')
			{
				syntax_errors(S, data);
				return (1);
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	check_input(char *s, t_data *data)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (ft_is_space(s[i]) == 1)
			;
		else if (s[i] == PIPE && check_pipe(s, i, quote, data))
			return (1);
		else if (s[i] == S || s[i] == D)
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
			if (check_open_quote(s, data))
				return (1);
		}
	}
	return (0);
}
