/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:31:35 by antoine           #+#    #+#             */
/*   Updated: 2023/11/08 15:18:27 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

t_buff	*fill_buff(int fd)
{
	t_buff	*buff;

	buff = (t_buff *) calloc(1, sizeof(t_buff));
	if (buff == NULL)
		return (NULL);
	buff->len = read(fd, buff->content, BUFFER_SIZE);
	buff->cursor = 0;
	if (buff->len == 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

ssize_t	read_line(char *s, size_t start)
{
	size_t	i;

	i = start - 1;
	while (++i < BUFFER_SIZE)
		if (s[i] == '\n' || s[i] == '\0')
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
		buff = fill_buff(fd);
	if (buff == NULL || buff->len == -1 || buff->len == 0)
		return (NULL);
	line = calloc(1, sizeof(char));
	line_len = 0;
	readed = -1;
	while (readed == -1)
	{
		readed = read_line(buff->content, buff->cursor);
		if (readed == -1) // end of line
		{
			line = caldupcat(line, buff->content + buff->cursor, line_len, BUFFER_SIZE - buff->cursor + 1);
			line_len += BUFFER_SIZE - buff->cursor;
			free(buff);
			buff = fill_buff(fd);
		}
		else
		{
			line = caldupcat(line, buff->content + buff->cursor, line_len, readed + 1);
			line_len += readed;
			buff->cursor += readed + 1;
		}
		if (buff->content[buff->cursor] == '\0') {
			free(buff);
			buff = NULL;
		}
	}
	return (line);
}

// int main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	fd = 0;
// 	if (argc >= 2)
// 		fd = open(argv[1], O_RDONLY);
// 	printf("fd: %d\n", fd);
// 	while (line != NULL)
// 	{
// 		line = get_next_line(fd);
// 		printf(".%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
