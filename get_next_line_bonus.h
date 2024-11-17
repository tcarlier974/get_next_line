/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:52 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 23:53:57 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line.h */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_gnl
{
	char	*buf;
	ssize_t	pos;
}	t_gnl;

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif