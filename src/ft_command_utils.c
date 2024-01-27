/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:12:59 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:13:00 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_count_commands(char *s)
{
	int	count;
	int	i;
	int	q;

	i = 0;
	q = 0;
	count = 0;
	while (s[i])
	{
		if (q == 0 && is_quote(s[i]))
			q = s[i] % 2 + 1;
		else if (is_quote(s[i]) && q == s[i] % 2 + 1)
			q = 0;
		while (s[i] == PIPE && q == 0)
			i++;
		if (s[i] && s[i] != PIPE && (q == 0 || i == 0))
			count++;
		while (s[i] && (s[i] != PIPE || q != 0))
			i++;
	}
	return (count);
}

void	*ft_free_command(char **new)
{
	int	i;

	i = 0;
	while (new && new[i])
	{
		free(new[i]);
		i++;
	}
	if (new)
		free(new);
	return (NULL);
}
