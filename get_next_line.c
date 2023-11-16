/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:41:59 by averin            #+#    #+#             */
/*   Updated: 2023/11/16 12:29:39 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_valid(char *line)
{
	if (!line)
		return (FALSE);
	return (line[ft_strlen(line) - 1] == '\n');
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*process;
	char		*line;

	line = NULL;
	process = NULL;
	while (!is_valid(line) && read_file(fd, (char **) &buffer))
	{
		process = process_buffer(buffer); //! Can return null
		if (!process)
			return (free(line), NULL); //! line to free
		if (line)
			line = ft_strcat(line, process); //! can be null
		else 
			line = process;
	}
	return (line);
}

int	read_file(int fd, char **buffer)
{
	int	readed;

	if (!buffer[0])
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if(readed <= 0)
			return (FALSE);
	}
	return (TRUE);
}

char	*process_buffer(char *buffer)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = find_end_line(buffer);
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = buffer[i];
	line[i] = '\0';
	ft_shift_str(buffer, len, BUFFER_SIZE); //! could ko when len == BUFFER_SIZE
	return (line);
}
