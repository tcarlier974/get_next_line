/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 21:48:08 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_lst	*l;
	int				i;
	int				c;
	char			*res;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!l && !(ft_lst_init(&l, fd)))
		return (NULL);
	c = ft_find_fd(&l, fd);
	i = 1;
	while (i > 0 && ft_new_line(l->buff[c / 2]))
	{
		tmp = ft_realloc(l->buff[c / 2],
				ft_l(l->buff[c / 2]), 
				ft_l(l->buff[c / 2]) + BUFFER_SIZE);
		if (!tmp)
			return (NULL);
		l->buff[c / 2] = tmp;
		i = read(fd, l->buff[c / 2] + ft_l(l->buff[c / 2]), BUFFER_SIZE);
		if (i > 0)
			l->buff[c / 2][ft_l(l->buff[c / 2]) + i] = '\0';
	}
	if (i < 0 || (!i && !l->buff[c / 2][0]))
		return (NULL);
	if (i == 0)
		res = ft_sub(tmp, 0, ft_l(l->buff[c / 2]));
	else
		res = ft_sub(tmp, 0, ft_s(l->buff[c / 2], '\n') + 1);
	if (res)
	{
		l->buff[c / 2] = ft_sub(l->buff[c / 2], ft_l(res), ft_l(l->buff[c / 2]));
		free(tmp);
	}
	return (res);
}

char	*ft_sub(char *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	if (start >= ft_l(s))
	{
		res = malloc(1);
		res[0] = '\0';
		return (res);
	}
	if (ft_l(s) < len + start)
		len = ft_l(s) - start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

int	ft_s(const char *s, int c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return ((int)ft_l((char *)s));
	return (res);
}

size_t	ft_l(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src
	, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_l(src));
}


int	main(void)
{
	int fd1;
	char *line;
	
	fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
		return (0);
	line = get_next_line(fd1);
	printf("%s\n", line);
	line = get_next_line(fd2);
	printf("%s\n", line);
	close(fd1);
	close(fd2);
	return (0);
}