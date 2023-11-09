/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:31:39 by antoine           #+#    #+#             */
/*   Updated: 2023/11/09 10:32:07 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = s;
	i = -1;
	while (++i < n)
		*p++ = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;
	size_t	x;

	x = nmemb * size;
	if (size != 0 && x / size != nmemb)
		return (NULL);
	r = malloc(nmemb * size);
	if (!r)
		return (NULL);
	ft_memset(r, 0, nmemb * size);
	return (r);
}

char	*caldupcat(char *origin, char *add, size_t origin_len, size_t add_len)
{
	char	*r;
	size_t	i;

	r = (char *) malloc((origin_len + add_len + 1) *sizeof(char));
	if (r == NULL)
		return (NULL);
	i = -1;
	while (++i < origin_len)
		r[i] = origin[i];
	--i;
	while (++i < origin_len + add_len)
		r[i] = add[i - origin_len];
	r[i] = '\0';
	free(origin);
	return (r);
}
