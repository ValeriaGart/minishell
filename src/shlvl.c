#include "minishell.h"

void	ft_export_shlvl(t_env **env, char *tok_val)
{
	t_env	*shlvl_pointer;
	int		i;

	i = 6;
	shlvl_pointer = ft_is_env(*env, "SHLVL=", 0);
	shlvl_pointer->str[6] = '0';
	if (ft_isdigit(tok_val[6]))
	{
		while(tok_val[i])
		{
			if (!ft_isdigit(tok_val[i]))
				return ;
			i++;
		}
		if (!tok_val[6] || tok_val[6] == '0')
			return ;
		if (i > 7)
			shlvl_pointer->str[6] = '9';
		else
			shlvl_pointer->str[6] = tok_val[6] - 1;
	}
}

int	ft_new_shlvl(t_env **env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	new->str = ft_strdup("SHLVL=0");
	if (!(new->str))
	{
		free(new);
		return (1);
	}
	new->next = *env;
	*env = new;
	return (0);
}

int	ft_shlvl(t_env **env)
{
	t_env	*new;
	int		i;

	i = 0;
	new = ft_is_env(*env, "SHLVL=", 0);
	if (!new)
		return (ft_new_shlvl(env));
	while (new->str[i] != '=')
		i++;
	if (new->str[i + 1] == '9' || new->str[i + 2] != '\0')
		new->str[i + 1] = '9';
	else
		new->str[i + 1] = new->str[i + 1] + 1;
	new->str[i + 2] = '\0';
	return (0);
}
