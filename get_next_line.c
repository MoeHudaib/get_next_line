#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static char	*read_until_newline(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	len = 0;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		line[i] = stash[i];
	return (line);
}

static char	*trim_stash(char *stash)
{
	size_t	start = 0;
	char	*new_stash;

	while (stash[start] && stash[start] != '\n')
		start++;
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + start + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	if (fd == -1)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}