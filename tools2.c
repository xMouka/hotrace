/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalyout <fbalyout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:25:21 by fbalyout          #+#    #+#             */
/*   Updated: 2025/04/20 18:25:22 by fbalyout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hot_race.h"

char	*ft_strdup(const char *str)
{
	int		len;
	char	*result;
	char	*dest;

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	dest = result;
	while ((*dest++ = *str++))
		;
	return (result);
}

char	*ft_strdup_len(const char *str, int len)
{
	char	*result;
	char	*dest;
	int		i;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	dest = result;
	i = 0;
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[len] = '\0';
	return (result);
}

void	ft_putstr(const char *str, int len)
{
	write(1, str, len);
}

unsigned long	hash1(const char *str, int len)
{
	unsigned long		hash;
	const unsigned char	*s;
	int					i;

	s = (const unsigned char *)str;
	hash = 0x811C9DC5;
	i = 0;
	while (i < len)
	{
		hash ^= s[i];
		hash *= 0x01000193;
		i++;
	}
	return (hash);
}

unsigned long	hash2(const char *str, int len, unsigned int prime)
{
	unsigned long		hash;
	const unsigned char	*s;
	int					i;

	hash = 0;
	s = (const unsigned char *)str;
	i = 0;
	while (i < len)
	{
		hash += s[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return ((hash % prime) | 1);
}
