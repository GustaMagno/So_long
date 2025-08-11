/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:15:15 by gustoliv          #+#    #+#             */
/*   Updated: 2025/05/18 21:49:42 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	s[BUFFER_SIZE + 1];
	char		*line;
	int			size;
	
	line = NULL;
	size = 1;
	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	while (size)
	{	
		if (*s == '\0')
			size = read(fd, s, BUFFER_SIZE);
		if (size < 0)
			return (clean_buffer(s, 1), free(line), NULL);
		if (size)
		{
			line = ft_strjoin(line, s, line);
			if (!check_newline(s))
				return (clean_buffer(s, 0), line);
			clean_buffer(s, 0);
		}
	}
	return (line);
}
