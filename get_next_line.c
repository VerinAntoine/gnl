/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:41:59 by averin            #+#    #+#             */
/*   Updated: 2023/11/15 16:49:08 by averin           ###   ########.fr       */
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
	// while (!buffer[0] && read_file(fd, (char **) &buffer))
	while (read_file(fd, (char **) &buffer) && !is_valid(line))
	{
		process = process_line(buffer);
		if (!process)
			return (NULL); //! line to free
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

char	*process_line(char *buffer)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = find_end_line(buffer);
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = -1;
	while (++i <= len)
		line[i] = buffer[i];
	line[i] = '\0';
	ft_shift_str(buffer, len + 1, BUFFER_SIZE); //! could ko when len == BUFFER_SIZE
	return (line);
}
