#include "../incl/minishell.h"

/* we get the letters after the '=' in environment */
char	*ft_get_var(char *str, t_data *data)
{
	int		i;
	t_env	*env;
	char	*var;

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
	var = ft_strdup((char *)&env->str[++i]);
	if (!var)
		return (NULL);
	return (var);
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

char	*ft_expander(char *str, t_data *data)
{
	int		q;
	int		i;
	char	*new;

	q = 0;
	i = -1;
	new = ft_strdup("");
	while (new && str[++i])
	{
		if (q == 0 && is_quote(str[i]))
			q = str[i] % 2 + 1;
		else if (is_quote(str[i]) && q == str[i] % 2 + 1)
			q = 0;
		if (str[i] == '\\' && q != 2)
		{
			new = ft_strjoin_char(new, str[i + 1]);
			if (str[i + 1])
				i++;
		}
		else if (q != 2 && str[i] == '$' && str[i + 1]
			&& ((is_quote(str[i + 1]) && q == 0) || ((ft_isalnum(str[i + 1])) && str[i + 1] != '\0')))
			new = expander_unquote(data, str, &i, new);
		else if (q != 2 && str[i] == '$' && str[i + 1] == '?' && ((!str[i + 2]
					|| ft_is_space(str[i + 2])) || str[i + 2]))
			new = ft_expand_global(&i, new);
		else
			new = ft_strjoin_char(new, str[i]);
	}
	free(str);
	return (new);
}
