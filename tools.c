#include "hot_race.h"

int	ft_strlen(const char *string)
{
	int i;
	
	i = 0;
	while (string[i++]) ;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (*s1 != *s2)
		return (*s1 - *s2);
	if (!*s1)
		return (0);
	if (*(s1 + 1) != *(s2 + 1))
		return (*(s1 + 1) - *(s2 + 1));
	if (!*(s1 + 1))
		return (0);
	s1 += 2;
	s2 += 2;
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

unsigned int	ft_sqrt(unsigned int x)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	ans;
	unsigned int	mid;

	if (x == 0 || x == 1)
		return (x);
	start = 1;
	end = x / 2;
	ans = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid <= x / mid)
		{
			ans = mid;
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
	return (ans);
}

int	is_prime(unsigned int n)
{
	unsigned int	i;
	unsigned int	sqrt_n;

	if (n <= 1)
		return (0);
	if (n <= 3)
		return (1);
	if (n % 2 == 0 || n % 3 == 0)
		return (0);
	sqrt_n = ft_sqrt(n);
	for (i = 5; i <= sqrt_n; i += 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return (0);
	}
	return (1);
}

unsigned int	next_prime(unsigned int n)
{
	if (n <= 1)
		return (2);
	if (n % 2 == 0)
		n++;
	while (!is_prime(n))
	{
		n += 2;
	}
	return (n);
}


