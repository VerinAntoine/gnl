/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:31:35 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 11:12:38 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff	*fill_buff(int fd, t_buff *buff)
{
	if (buff != NULL)
		free(buff);
	buff = (t_buff *) ft_calloc(1, sizeof(t_buff));
	if (buff == NULL)
		return (NULL);
	buff->len = read(fd, buff->content, BUFFER_SIZE);
	buff->cursor = 0;
	if (buff->len == 0 || buff->len == -1)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

ssize_t	line_length(char *s, size_t start)
{
	size_t	i;

	i = start - 1;
	while (++i < BUFFER_SIZE)
		if (s[i] == '\n' || s[i] == '\0')
			return (i - start);
	return (-1);
}

ssize_t	process_buffer(char **line, t_buff **buff, size_t *line_len, int fd)
{
	ssize_t	readed;

	readed = line_length((*buff)->content, (*buff)->cursor);
	if (readed == -1)
	{
		*line = caldupcat(*line, (*buff)->content + (*buff)->cursor, *line_len,
				BUFFER_SIZE - (*buff)->cursor + 1);
		*line_len += BUFFER_SIZE - (*buff)->cursor;
		*buff = fill_buff(fd, *buff);
	}
	else
	{
		*line = caldupcat(*line, (*buff)->content + (*buff)->cursor, *line_len,
				readed + 1);
		*line_len += readed;
		(*buff)->cursor += readed + 1;
	}
	return (readed);
}

char	*get_next_line(int fd)
{
	static t_buff	*buff;
	char			*line;
	size_t			line_len;

	if (buff == NULL || buff->cursor >= buff->len)
		buff = fill_buff(fd, buff);
	if (buff == NULL)
		return (NULL);
	line = calloc(1, sizeof(char));
	line_len = 0;
	while (buff != NULL && process_buffer(&line, &buff, &line_len, fd) == -1)
	{
		if (buff != NULL && buff->content[buff->cursor] == '\0')
		{
			free(buff);
			buff = NULL;
		}
	}
	return (line);
}
