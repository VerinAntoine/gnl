/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:42:36 by averin            #+#    #+#             */
/*   Updated: 2023/11/17 10:50:56 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# define FALSE 0
# define TRUE 1
# define FD_MAX 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

char	*get_next_line(int fd);
int		read_file(int fd, char **buffer);
char	*process_buffer(char *buffer);
int		is_valid(char *line);

size_t	find_end_line(char *s);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *s1, char *s2);
void	ft_shift_str(char *s, size_t shift, size_t len);

#endif