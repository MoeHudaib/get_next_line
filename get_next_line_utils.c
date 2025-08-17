/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:51:53 by mohammad          #+#    #+#             */
/*   Updated: 2025/08/17 17:51:53 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	grow_buffer(int buffer)
{
	buffer *= 2;
	return (buffer);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total;
	unsigned char	*ptr;
	size_t			i;

	total = count * size;
	ptr = (unsigned char *)malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

void	*ft_realloc(void *ptr, int *old_size, int (*f)(int))
{
	void	*new_ptr;
	int		i;
	int		new_size;

	new_size = f(*old_size);
	if (!ptr)
		return (ft_calloc(new_size, sizeof(char)));
	new_ptr = ft_calloc(new_size, sizeof(char));
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < *old_size && i < new_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	((char *)new_ptr)[i] = '\0';
	free(ptr);
	*old_size = new_size;
	return (new_ptr);
}

int	set_it_in(char **str, char c, int *buffer)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i])
		i++;
	if (i >= *buffer - 1)
	{
		tmp = ft_realloc(*str, buffer, grow_buffer);
		if (!tmp)
			return (-1);
		*str = tmp;
	}
	(*str)[i++] = c;
	(*str)[i] = '\0';
	return (0);
}
