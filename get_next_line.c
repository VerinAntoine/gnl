/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:31:35 by antoine           #+#    #+#             */
/*   Updated: 2023/11/08 11:46:30 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

t_buff	*read_fd(int fd)
{
	t_buff	*buff;

	buff = (t_buff *) malloc(sizeof(t_buff));
	if (buff == NULL)
		return (NULL);
	buff->len = read(fd, buff->content, BUFFER_SIZE);
	buff->cursor = 0;
	return (buff);
}

ssize_t	find_line(char *s, size_t start)
{
	size_t	i;

	i = start - 1;
	while (++i < BUFFER_SIZE)
		if (s[i] == '\n')
			return (i - start);
	return (-1);
}

char	*get_next_line(int fd)
{
	static t_buff	*buff;
	char			*line;
	size_t			line_len;
	ssize_t			readed;

	if (buff == NULL || buff->cursor == BUFFER_SIZE)
		buff = read_fd(fd);
	if (buff == NULL || buff->len == -1 || buff->len == 0)
		return (NULL);
	line = calloc(1, sizeof(char));
	line_len = 0;
	readed = -1;
	while (readed == -1)
	{
		readed = find_line(buff->content, buff->cursor);
		if (readed == -1)
		{
			line = caldupcat(line, buff->content + buff->cursor, line_len, BUFFER_SIZE - buff->cursor);
			line_len += BUFFER_SIZE - buff->cursor;
			free(buff);
			buff = read_fd(fd);
		}
		else
		{
			line = caldupcat(line, buff->content + buff->cursor, line_len, readed);
			line_len += readed;
			buff->cursor += readed + 1;
		}
	}
	return (line);
}

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	line = get_next_line(fd);
	printf(".%s\n", line);
	free(line);
	close(fd);
}
