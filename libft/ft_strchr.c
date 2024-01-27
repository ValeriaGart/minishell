/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vharkush <vharkush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:00:05 by ynguyen           #+#    #+#             */
/*   Updated: 2024/01/27 12:56:41 by vharkush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	if (c >= 128)
		c %= 128;
	while (s && *s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (s && *s == c)
		return ((char *)s);
	return (0);
}
