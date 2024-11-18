/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:52 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/18 12:45:53 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line.h */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_gnl
{
	char	*buf;
	ssize_t	pos;
	int		tab;
	int		c;
}	t_gnl;

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif