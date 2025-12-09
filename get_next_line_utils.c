/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:35:07 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/03 14:35:07 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	x = (unsigned char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == x)
			return ((char *)&s[i]);
		i++;
	}
	if (x == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	int		x;
	int		y;
	size_t	ls1;
	size_t	ls2;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if ((!s1 && !s2) || (ls1 == 0 && ls2 == 0))
		return (NULL);
	ns = malloc(ls1 + ls2 + 1);
	if (ns == NULL)
		return (NULL);
	x = 0;
	y = 0;
	if (s1 != NULL)
		while (s1[y])
			ns[x++] = s1[y++];
	y = 0;
	if (s2 != NULL)
		while (s2[y])
			ns[x++] = s2[y++];
	ns[x] = '\0';
	return (ns);
}
