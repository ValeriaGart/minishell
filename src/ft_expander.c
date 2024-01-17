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

char *ft_add_quotes(char *str, int i, int y)
{
	char	*tmp1;
	int 	str_len;
	int		words;

	words = ft_word_count(str);
	str_len = ft_strlen(str);
	tmp1 = ft_calloc(str_len + (words * 2) + 1, sizeof(char));
	tmp1[i] = D;
	i++;
	while (y < str_len)
	{
		if (ft_isspace(str[y]))
		{
			tmp1[i] = D;
			i++;
			while (ft_isspace(str[y]))
			{
				tmp1[i] = str[y];
				i++;
				y++;
			}
			tmp1[i] = D;
			i++;
		}
		else
		{
			tmp1[i] = str[y];
			i++;
			y++;
		}
	}
	tmp1[i] = D;
	i++;
	return (tmp1);
}

/* we get the letters after the '=' in environment */
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
	if (i || env == NULL || !env->str)
	{
		var = ft_strdup("");
		return (var);
	}
	i = 0;
	while (env->str[i] == str[i])
		i++;
	return (ft_add_quotes((char *)&env->str[++i], 0, 0));
}

/*we get the letters after the '='*/
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
	while (new && str[*i + 1] && ft_isalnum(str[*i + 1]))
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

int	ft_is_heredoc(char *new)
{
	int i;

	i = ft_strlen(new);
	if (!i)
		return (0);
	i--;
	if (new[i] == D)
		i--;
	while (i != -1 && ft_isspace(new[i]))
		i--;
	if (i > 0 && new[i] == '<' && new[i - 1] == '<')
	{
		while (i != -1 && new[i] == '<')
			i--;
		if (i == -1 || ft_isspace(new[i]))
			return (1);
	}
	return (0);
}

char	*process_character(char *str, char *new, int *i, t_data *data)
{
	if (str[*i] == '\\' && data->expander_q != 2)
	{
		new = ft_strjoin_char(new, str[*i + 1]);
		if (str[*i + 1])
			*i += 1;
	}
	else if (data->expander_q  != 2 && str[*i] == '$' && ((is_quote(str[*i + 1]) && data->expander_q  == 0)
		|| (((ft_isalnum(str[*i + 1])) && str[*i + 1] != '\0') && !ft_is_heredoc(new) && str[*i + 1])))
		new = expander_unquote(data, str, i, new);
	else if (data->expander_q  != 2 && str[*i] == '$' && str[*i + 1] == '?' && ((!str[*i + 2]
				|| ft_is_space(str[*i + 2])) || str[*i + 2]))
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

//Yen, i added data->expander_q value, because quotes weren't tracked properly ^^
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
			str = ft_str_expand_home(str, i); //TODO: make sure to free
		new = process_character(str, new, &i, data);
	}
	free(str);
	return (new);
}
