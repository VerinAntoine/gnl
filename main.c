/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:43:36 by averin            #+#    #+#             */
/*   Updated: 2023/11/09 09:43:52 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = 0;
	if (argc >= 2)
		fd = open(argv[1], O_RDONLY);
	printf("fd: %d\tbuffer_size: %d\n", fd, BUFFER_SIZE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf(".%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}