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
	return result;
}

char	*ft_strdup_len(const char *str, int len)
{
	char	*result;
	char	*dest;
	int		i;

	result = malloc(len + 1);
	if (!result)
		return NULL;
	dest = result;
    i = 0;
    while (i < len)
    {
		dest[i] = str[i];
        i++;
    }
	dest[len] = '\0';
	return result;
}

void	ft_putstr(const char *str, int len)
{
	write(1, str, len);
}

unsigned long	hash1(const char *str, int len)
{
	unsigned long		hash;
	const unsigned char	*s = (const unsigned char *)str;
	int					i;

	hash = 0x811C9DC5;
	for (i = 0; i < len; i++)
	{
		hash ^= s[i];
		hash *= 0x01000193;
	}
	return hash;
}

unsigned long	hash2(const char *str, int len, unsigned int prime)
{
	unsigned long hash = 0;
	const unsigned char *s = (const unsigned char *)str;
	int i;

	for (i = 0; i < len; i++)
	{
		hash += s[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return (hash % prime) | 1;
}
