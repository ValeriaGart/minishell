
#include "../incl/minishell.h"

t_dlist	*ft_create_dlist(char *s, int quote)
{
	t_dlist	*node;

	node = malloc(sizeof(t_dlist));
	if (!node)
		return (NULL);
	node->str = ft_strdup(s);
	node->quote = quote;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	ft_add_dlist_back(t_dlist **dl, char *str, int quote)
{
	t_dlist	*tmp;

	if (!*dl)
	{
		*dl = ft_create_dlist(str, quote);
		return ;
	}
	tmp = (*dl);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_create_dlist(str, quote);
	tmp->next->prev = tmp;
}

int	which_symbols(char *s, int q)
{
	if (q != 0)
		return (0);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, (char *)PIPE, 1) == 0)
		return (1);
	else
		return (0);
}
