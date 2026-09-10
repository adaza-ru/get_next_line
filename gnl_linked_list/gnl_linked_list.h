/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_linked_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:34:47 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/09/10 21:01:30 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_LINKED_LIST_H
# define GNL_LINKED_LIST_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	int				file_descriptor;
	char			*stash;
	struct s_gnl	*next;	
}		t_gnl;

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
t_gnl	*find_or_create(int fd, t_gnl **list);

#endif
