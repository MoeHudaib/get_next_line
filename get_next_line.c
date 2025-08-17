/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:51:46 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/17 17:51:47 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char	get_char(char **str, int fd, ssize_t *bytes, int *buffer)
{
	char	c;

	c = 0;
	*bytes = read(fd, &c, 1);
	if (*bytes > 0)
	{
		if (set_it_in(str, c, buffer) == -1)
			*bytes = -1;
	}
	return (c);
}

char	*get_next_line(int fd)
{
	ssize_t		bytes;
	char		*line;
	int			capacity;
	char		c;

	capacity = BUFFER_SIZE;
	if (fd < 0 || capacity <= 0)
		return (NULL);
	line = ft_calloc(capacity, sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	bytes = 1;
	c = get_char(&line, fd, &bytes, &capacity);
	while (c != '\n' && bytes == 1)
		c = get_char(&line, fd, &bytes, &capacity);
	if (bytes == -1 || (bytes == 0 && ft_strlen(line) == 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
