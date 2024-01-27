/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:13:05 by vharkush          #+#    #+#             */
/*   Updated: 2024/01/27 11:33:16 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_word_count(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (str && str[i] == '\0')
		return (space);
	while (str && str[i])
	{
		if (ft_isspace(str[i]))
		{
			space++;
			while (ft_isspace(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	return (space + 1);
}

void	find_dquote(char *str, char *tmp1, int *i, int *y)
{
	if (ft_isspace(str[*y]))
	{
		tmp1[*i] = D;
		(*i)++;
		while (ft_isspace(str[(*y)]))
			tmp1[(*i)++] = str[(*y)++];
		tmp1[(*i)] = D;
		(*i)++;
	}
	else
		tmp1[(*i)++] = str[(*y)++];
}

char	*ft_add_quotes(char *str, int i, int y)
{
	char	*tmp1;
	int		str_len;
	int		words;

	words = ft_word_count(str);
	str_len = ft_strlen(str);
	tmp1 = ft_calloc(str_len + (words * 2) + 1, sizeof(char));
	if (!tmp1)
		return (NULL);
	tmp1[i] = D;
	i++;
	while (y < str_len)
		find_dquote(str, tmp1, &i, &y);
	tmp1[i] = D;
	i++;
	return (tmp1);
}

char	*ft_get_var(char *str, t_data *data)
{
	int		i;
	t_env	*env;
	char	*var;

	var = NULL;
	env = data->env;
	i = after_dollar(*str);
	if (str[i] == D)
		env = NULL;
	else
		env = ft_is_env(env, str, ft_strlen_var(str));
	if (i || env == NULL || !env->str || (ft_strlen_var(str) + 1)
		== (int)ft_strlen(env->str))
	{
		var = ft_strdup("");
		return (var);
	}
	i = 0;
	while (env->str[i] == str[i])
		i++;
	return (ft_add_quotes((char *)&env->str[++i], 0, 0));
}

char	*ft_name_var(char *s)
{
	char			*var;
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != 32 && s[i] != D)
		i++;
	var = ft_calloc(sizeof(char), (i + 2));
	if (!var)
		return (NULL);
	var[i] = '=';
	while (i--)
		var[i] = s[i];
	return (var);
}
