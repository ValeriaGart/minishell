#include "../incl/minishell.h"

char *ft_add_quotes(char *str, int i, int y)
{
	char	*tmp1;
	int 	str_len;
	int		first_space;

	first_space = 0;
	str_len = ft_strlen(str);
	tmp1 = ft_calloc(str_len + 5, sizeof(char));
	while (y < str_len)
	{
		if (ft_isspace(str[y]) && !first_space)
		{
			tmp1[i] = str[y];
			tmp1[i + 1] = D;
			first_space = 1;
			i++;
		}
		else
			tmp1[i] = str[y];
		i++;
		y++;
	}
	if (first_space)
		tmp1[i] = D;
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
	int q;

	q = 0;
	if (q == 0 && is_quote(str[*i]))
		q = str[*i] % 2 + 1;
	else if (is_quote(str[*i]) && q == str[*i] % 2 + 1)
		q = 0;
	if (str[*i] == '\\' && q != 2)
	{
		new = ft_strjoin_char(new, str[*i + 1]);
		if (str[*i + 1])
			i++;
	}
	else if (q != 2 && str[*i] == '$' && ((is_quote(str[*i + 1]) && q == 0)
		|| (((ft_isalnum(str[*i + 1])) && str[*i + 1] != '\0') && !ft_is_heredoc(new) && str[*i + 1])))
		new = expander_unquote(data, str, i, new);
	else if (q != 2 && str[*i] == '$' && str[*i + 1] == '?' && ((!str[*i + 2]
				|| ft_is_space(str[*i + 2])) || str[*i + 2]))
		new = ft_expand_global(i, new);
	else
		new = ft_strjoin_char(new, str[*i]);
	return (new);
}

char	*ft_expander(char *str, t_data *data)
{
	int		i;
	char	*new;

	i = -1;
	new = ft_strdup("");
	while (new && str[++i])
		new = process_character(str, new, &i, data);
	free(str);
	return (new);
}
