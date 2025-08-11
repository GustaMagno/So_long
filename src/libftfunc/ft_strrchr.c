/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:52:21 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/11 20:23:23 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		keep;

	keep = -1;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			keep = i;
		i++;
	}
	if ((char)c == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	if (keep >= 0)
		return ((char *)&s[keep]);
	return (NULL);
}