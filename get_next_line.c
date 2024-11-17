/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 20:03:20 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_lst	*l;
	int				i;
	int				c;
	char			*res;

	if (fd == 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!l)
		ft_lst_init(&l, fd);
	c = ft_find_fd(l, fd);
	i = 1;
	while (ft_new_line(l->buff[c / 2]))
	{
		l->buff[c / 2] = ft_realloc(l->buff[c / 2],
				ft_l(l->buff[c / 2]),
				ft_l(l->buff[c / 2]) + BUFFER_SIZE);
		i = read(fd, l->buff[c / 2] + l->tab[c + 1], BUFFER_SIZE);
		l->tab[c + 1] += i;
	}
	if (i == 0)
		res = (ft_sub(l->buff[c / 2], 0, ft_l(l->buff[c / 2])));
	else
		res = (ft_sub(l->buff[c / 2], 0, ft_s(l->buff[c / 2], '\n') + 1));
	l->buff[c / 2] = ft_sub(l->buff[c / 2], ft_l(res), ft_l(l->buff[c / 2]));
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
	int fd;
	char *line;
	
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while ((line))
	{
		printf("%s", line);
		// free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}