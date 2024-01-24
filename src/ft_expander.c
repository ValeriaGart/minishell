#include "../incl/minishell.h"

char	*expander_unquote(t_data *data, char *str, int *i, char *new)
{
	char	*get_var;

	get_var = ft_get_var(&str[++(*i)], data);
	if (!get_var)
		return (ft_free_new(new));
	if (get_var[0] == '\0' && is_quote(str[*i]))
	{
		*i -= 1;
		return (free(get_var), new);
	}
	new = ft_strjoin_free(new, get_var);
	while (new && str[*i + 1] && (ft_isalnum(str[*i + 1])
			|| str[*i + 1] == '_'))
		++(*i);
	return (new);
}

char	*ft_expand_global(int *i, char *new)
{
	char	*get_var;

	get_var = ft_itoa(g_minishell);
	if (!get_var)
		return (ft_free_new(new));
	new = ft_strjoin_free(new, get_var);
	*i = *i + 1;
	return (new);
}

char	*process_character(char *str, char *new, int *i, t_data *data)
{
	if (str[*i] == '\\' && data->expander_q != 2)
	{
		new = ft_strjoin_char(new, str[*i + 1]);
		if (str[*i + 1])
			*i += 1;
	}
	else if (data->expander_q != 2 && str[*i] == '$' && ((is_quote(str[*i + 1])
				&& data->expander_q == 0) || ((str[*i + 1] != '\0'
					&& ((ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')))
				&& !ft_is_heredoc(new) && str[*i + 1])))
		new = expander_unquote(data, str, i, new);
	else if (data->expander_q != 2 && str[*i] == '$' && str[*i + 1] == '?'
		&& ((!str[*i + 2] || ft_is_space(str[*i + 2])) || str[*i + 2]))
		new = ft_expand_global(i, new);
	else
		new = ft_strjoin_char(new, str[*i]);
	return (new);
}

char	*ft_str_expand_home(char *str, int i)
{
	char	*ret;

	ret = ft_calloc(sizeof(char), ft_strlen(str) + 5);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i + 1);
	ft_strlcpy(ret + i, "$HOME", 5 + 1);
	i++;
	ft_strlcpy(ret + i + 4, str + i, ft_strlen(str + i) + 1);
	free (str);
	return (ret);
}

char	*ft_expander(char *str, t_data *data)
{
	int		i;
	char	*new;

	i = -1;
	data->expander_q = 0;
	new = ft_strdup("");
	while (new && str[++i])
	{
		if (data->expander_q == 0 && is_quote(str[i]))
			data->expander_q = str[i] % 2 + 1;
		else if (is_quote(str[i]) && data->expander_q == str[i] % 2 + 1)
			data->expander_q = 0;
		if (str[i] == '~' && data->expander_q != 2 && !ft_is_heredoc(new)
			&& (str[i + 1] == '\0' || ft_isspace(str[i + 1])))
			str = ft_str_expand_home(str, i);
		new = process_character(str, new, &i, data);
	}
	free(str);
	return (new);
}
