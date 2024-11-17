/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 17:25:33 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_lst	*lst;
	char			*res;
	int				i;
	int				c;
	
	if (fd == 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!lst)
		ft_lst_init(&lst, fd);
	c = ft_find_fd(lst, fd);
	i = -1;
	while(ft_new_line(lst->buff[c / 2]) != 0 || i != 0)
	{
		lst->buff[c / 2] = ft_realloc(lst->buff[c / 2], ft_strlen(lst->buff[c / 2]),
			ft_strlen(lst->buff[c / 2]) + BUFFER_SIZE);
		i += read(fd, lst->buff[c / 2] + lst->tab[c + 1], BUFFER_SIZE);
	}
	lst->tab[c + 1] = i + 1;
	if (i == 0)
		return (ft_substr(lst->buff[c / 2], lst->tab[c + 1], ft_strlen(lst->buff[c / 2])));
	else
		return (ft_substr(lst->buff[c / 2], lst->tab[c + 1], ft_s(lst->buff[c / 2], '\n') + 1));
	return (res);
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		res = malloc(1);
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen(s) < len + start)
		len = ft_strlen(s) - start;
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
			res = i;
		i++;
	}
	if ((char)c == '\0')
		return ((int)ft_strlen((char *)s));
	if (res == 0 && s[0] != (char)c)
		return (0);
	return (res);
}
size_t	ft_strlen(char *str)
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
	return (ft_strlen(src));
}


int	main(void)
{
	int fd;
	char *line;
	
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}