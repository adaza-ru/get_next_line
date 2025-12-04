/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:32:29 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/03 14:32:29 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_stash(char	*stash, size_t	i)
{
	char	*ns;
	size_t	j;

	j = 0;
	while(stash[j] != '\0')
		j++;
	ns = malloc((j - i) * sizeof(char) + 1);
	if (ns == NULL)
		return (NULL);
	j = 0;
	while ((stash[j + i] != '\0'))
	{
		ns[j] = stash[j + i];
		i++;
	}
	ns[j] = '\0';
	return (ns);
}

char	*fetch_line(char	*stash,	char eol)
{
	char	*line;
	size_t	i;
	char	*tmp;

	i = 0;
	while(stash[i] != '\0' && stash[i] != eol)
		i++;
	line = malloc(i * sizeof(char) + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != eol)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	tmp = stash;
	stash = new_stash(stash, (i));
	free(tmp);
	return (line);
}

char *get_next_line(int fd)
{
	static char	*stash;
	char	*line;
	int	read_state;
	char	*temp_stash;

	temp_stash = "";
	if(fd < 0 | read(fd, temp_stash, 0) < 0 | BUFFER_SIZE < 0)
		return (NULL);
	read_state = 1;
	while(ft_strchr(stash, '\n') == NULL && read_state > 0)
	{
		read_state = read(fd, temp_stash, BUFFER_SIZE);
		stash = ft_strjoin(stash, temp_stash);
	}
	return (fetch_line(stash, '\n'));
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("lorem.txt", O_RDONLY | O_CREAT, 0644);
	char *s = get_next_line(fd);
	while(s != NULL)
	{
		printf("%s\n", s);
		s = get_next_line(fd);
	}
	return(0);
}