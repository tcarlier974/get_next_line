/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:52 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 21:50:55 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_lst
{
	int		*tab;
	char	**buff;
}	t_lst;

char	*get_next_line(int fd);
t_lst	*ft_lst_init(t_lst **lst, int fd);
int		ft_find_fd(t_lst **lst, int fd);
void	*ft_realloc(void *buff, size_t old, size_t new);
void	*ft_realloc_int(void *buff, size_t olds, size_t news);
void	ft_lst_add_back(t_lst **lst, int fd);
int		ft_c(const char *s, int c);
char	*ft_s(char *s, unsigned int start, size_t len);
size_t	ft_l(char *str);
int		ft_new_line(char *buff);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);

#endif