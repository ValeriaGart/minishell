
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
	else if (ft_strncmp(s, PIPE, 1) == 0)
		return (1);
	else
		return (0);
}

t_tlist	*tokenize(t_dlist *v, t_tlist *sing, t_data *j)
{
	t_tlist			*p;
	unsigned int	i;

	if (j->at == 1)
		sing = ft_create_tlist();
	p = sing;
	if (j->at == 2)
	{
		ft_add_tlist_back(&p);
		while (sing->next != 0)
			sing = sing->next;
	}
	i = 0;
	while (v != 0)
		token_loop(&v, &sing, &i, p);
	if (sing != 0 && sing->flargs != 0)
		sing->flargs[i] = 0;
	return (p);
}

void	token_loop(char *s, int *q, int *i, int **sum_q)
{
	(*sum_q)[2] = 0;
	while (s[*i] && (ft_is_space(s[*i]) == 1) && which_symbols(&s[*i], *q) == 0)
	{
		if ((*q == 0 && (s[*i] == S || s[*i] == D)) && (((*sum_q)[0] != 0
					&& s[*i] == D) || ((*sum_q)[1] != 0 && s[*i] == S)))
		{
			(*sum_q)[s[*i] % 2]--;
			*q = 1 + (s[*i] % 2);
		}
		else if ((*q == 2 && s[*i] == S) || (s[*i] == D && *q == 1))
		{
			(*sum_q)[2] = *q;
			*q = 0;
		}
		(*i)++;
	}
}

void	get_tokens(char *s, t_dlist **doub, int quote[3])
{
	unsigned int i;
	unsigned int start;
	int q;

	start = 0;
	i = 0;
	q = 0;
	while (s[i])
	{
		quote
	}
}