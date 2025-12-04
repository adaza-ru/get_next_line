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

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	x = (unsigned char)c;
	i = 0;
	if (*s == '\0' && c != 0)
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

	if (!s1 || !s2)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x] != '\0')
		x++;
	while (s2[y] != '\0')
		y++;
	ns = malloc(sizeof(char) * (x + y + 1));
	if (ns == NULL)
		return (NULL);
	x = -1;
	y = -1;
	while (s1[++x] != '\0')
		ns[x] = s1[x];
	while (s2[++y] != '\0')
		ns[x + y] = s2[y];
	ns[x + y] = '\0';
	return (ns);
}