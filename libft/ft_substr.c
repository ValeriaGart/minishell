/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:47:07 by ynguyen           #+#    #+#             */
/*   Updated: 2022/10/25 19:19:36 by ynguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*substr;

	if (start >= ft_strlen(s))
		len = 0;
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	substr = malloc(len + 1);
	i = 0;
	if (!substr)
		return (NULL);
	while (len > 0)
	{
		substr[i] = s[start];
		len--;
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
