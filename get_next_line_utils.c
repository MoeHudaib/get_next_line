#include "get_next_line.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total = count * size;
	size_t	i = 0;

	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	len = ft_strlen(s);
	char	*dup = ft_calloc(len + 1, sizeof(char));
	size_t	i = 0;

	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	char	*joined = ft_calloc(len1 + len2 + 1, sizeof(char));
	size_t	i = 0, j = 0;

	if (!joined)
		return (NULL);
	while (s1 && s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		joined[j++] = s2[i++];
	if (s1)
		free(s1);
	return (joined);
}
