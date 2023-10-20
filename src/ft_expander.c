
#include "../incl/minishell.h"

char	*implement_after_dollar(char c)
{
	if (c == '0')
		return (ft_strdup("minishell"));
	else if (c == '?')
		return (ft_itoa(minishell_global));
	else
		return (NULL);
}

int	after_dollar(char next)
{
	if (next && (next == '?' || next == '0'))
		return (1);
	return (0);
}
int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != 32 && !is_quote(str[i]))
		i++;
	return (i);
}
/* we get the letters after the '=' in environment */
char	*ft_get_var(char *str, t_data *data)
{
	int		i;
	t_env	*env;
	char	*var;

	i = 0;
	env = data->env;
	if (after_dollar(*str))
		return (implement_after_dollar(*str));
	while (env && env->str)
	{
		if (!ft_strncmp((char *)env->str, str, ft_strlen_var(str)))
			break ;
		env = env->next;
	}
	if (env == NULL || !env->str)
		return (NULL);
	while (env->str[i] == str[i])
		i++;
	var = ft_strdup((char *)&env->str[++i]);
	if (!var)
		return (NULL);
	return (var);
}
/**/

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

// char	*ft_new_length(char *str, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	*new;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
// 		{
// 			j += ft_strlen(ft_get_var(data, ft_name_var(&str[++i])));
// 			while (str[i] && str[i] != 32 && (str[i] != S && str[i] != D))
// 			{
// 				i++;
// 				j--;
// 			}
// 		}
// 		else
// 			i++;
// 	}
// 	new = ft_calloc(sizeof(char), i + j + 1);
// 	if (!new)
// 		return (NULL);
// 	return (new);
// }

char	*ft_expander(char *str, t_data *data)
{
	int		q;
	int		i;
	char	*new;

	q = 0;
	i = 0;
	// new = ft_new_length(str, data);
	new = ft_strdup("");
	while (str[i])
	{
		if (q == 0 && is_quote(str[i]))
			q = str[i] % 2 + 1;
		else if (is_quote(str[i]) && q == str[i] % 2 + 1)
			q = 0;
		else if (q != 2 && str[i] == '$')
		{
			new = ft_strjoin_free(new, ft_get_var(&str[++i], data));
			while (str[i + 1] && str[i + 1] != 32 && !is_quote(str[i + 1]))
				i++;
		}
		else
			new = ft_strjoin_char(new, str[i]);
		i++;
	}
	return (new);
}
