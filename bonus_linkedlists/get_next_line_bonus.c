/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:34:08 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/03 14:34:08 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*new_stash(char *stash, char eol)
{
	char	*ns;
	size_t	j;
	size_t	i;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[i] != '\0' && stash[i] != eol)
		i++;
	if (stash[i] == eol)
		i++;
	j = ft_strlen(stash);
	ns = malloc((j - i + 1) * sizeof(char));
	if (ns == NULL)
		return (NULL);
	j = 0;
	while ((stash[j + i] != '\0'))
	{
		ns[j] = stash[j + i];
		j++;
	}
	ns[j] = '\0';
	free(stash);
	return (ns);
}

static char	*fetch_line(char	*stash,	char eol)
{
	char	*line;
	size_t	i;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != eol)
		i++;
	if (stash[i] == eol)
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	line[i] = '\0';
	while (--i > 0)
		line[i] = stash[i];
	line[0] = stash[0];
	return (line);
}

static int	read_to_stash(int fd, char **stash, char *buffer)
{
	int		read_state;
	char	*tmp_str;

	read_state = 1;
	while (ft_strchr(*stash, '\n') == NULL && read_state > 0)
	{
		read_state = read(fd, buffer, BUFFER_SIZE);
		if (read_state < 0)
		{
			free(*stash);
			*stash = NULL;
			return (0);
		}
		buffer[read_state] = '\0';
		tmp_str = ft_strjoin(*stash, buffer);
		free(*stash);
		*stash = tmp_str;
		if (*stash == NULL && read_state == 0)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl	*list;
	char			*line;
	char			*buffer;
	t_gnl			*ptr;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (0);
	ptr = find_or_create(fd, list);
	if (read_to_stash(fd, &stash[fd], buffer) == 0)
	{
		free(buffer);
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = fetch_line(stash[fd], '\n');
	stash[fd] = new_stash(stash[fd], '\n');
	free(buffer);
	return (line);
}
