/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:24:48 by antoine           #+#    #+#             */
/*   Updated: 2023/11/08 13:14:06 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_buff {
	char	content[BUFFER_SIZE];
	ssize_t	len;
	size_t	cursor;
}	t_buff;

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
char	*caldupcat(char *origin, char *add, size_t origin_len, size_t add_len);

#endif
