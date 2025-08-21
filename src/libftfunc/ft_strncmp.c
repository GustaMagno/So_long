/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:54:43 by gustoliv          #+#    #+#             */
/*   Updated: 2025/08/11 20:23:45 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cont1;

	cont1 = 0;
	while (cont1 < n)
	{
		if (s1[cont1] != s2[cont1] || s1[cont1] == '\0' || s2[cont1] == '\0')
			return ((unsigned char)s1[cont1] - (unsigned char)s2[cont1]);
		cont1++;
	}
	return (0);
}