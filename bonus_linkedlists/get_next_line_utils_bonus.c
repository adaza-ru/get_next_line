/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:35:36 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/03 14:35:36 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (ls1 != 0)
		while (s1[y])
			ns[x++] = s1[y++];
	y = 0;
	if (ls2 != 0)
		while (s2[y])
			ns[x++] = s2[y++];
	ns[x] = '\0';
	return (ns);
}
t_gnl	*find_or_create(int fd, t_gnl *list)
{
	t_gnl	*ptr;

	if (!new)
		return ;
	ptr = lst[0];
	if (ptr == NULL)
	{
		lst[0] = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return(ptr);
}