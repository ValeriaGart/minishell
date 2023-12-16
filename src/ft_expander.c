
#include "../incl/minishell.h"

/*char	*implement_after_dollar(char c)
{
	if (c == '0')
		return (ft_strdup("minishell"));
	else if (c == '?')
		return (ft_itoa(minishell_global));
	else
		return (NULL);
}*/

int	after_dollar(char next)
{
	if (next && (next == '?' || next == '0'))
		return (1);
	return (0);
}

/*we accept cases: after $ things can printable*/
int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}
/* we get the letters after the '=' in environment */
char	*ft_get_var(char *str, t_data *data)
{
	int		i;
	t_env	*env;
	char	*var;

	env = data->env;
	i = after_dollar(*str);
//	if (after_dollar(*str))
//		return (NULL);
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

char	*ft_expander(char *str, t_data *data)
{
	int		q;
	int		i;
	char	*new;
	char	*get_var;

	q = 0;
	i = -1;
	new = ft_strdup("");
	get_var = NULL;
	while (new && str[++i])
	{
		if (q == 0 && is_quote(str[i]))
			q = str[i] % 2 + 1;
		else if (is_quote(str[i]) && q == str[i] % 2 + 1)
			q = 0;
		if (q != 2 && str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]))
					&& str[i + 1] != '\0')
		{
			get_var = ft_get_var(&str[++i], data);
			if (!get_var)
				return (ft_free_new(new));
			new = ft_strjoin_free(new, get_var);
			while (new && str[i + 1] && ft_isalnum(str[i + 1]))
				i++;
		}
		else
			new = ft_strjoin_char(new, str[i]);
	}
	free(str);
	return (new);
}
