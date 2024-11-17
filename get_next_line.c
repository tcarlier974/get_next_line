/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 14:23:50 by tcarlier         ###   ########.fr       */
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
		ft_lst_init(lst, fd);
	c = ft_find_fd(lst, fd);
	i = -1;
	while(!(ft_new_line(lst->buff[c])) || i == 0);
	{
		ft_realloc(lst->buff[c], ft_strlen(lst->buff[c]),
			ft_strlen(lst->buff[c]) + BUFFER_SIZE);
		i = read(fd, lst->buff[c] + lst->tab[c + 1], BUFFER_SIZE);
	}
	if (i == 0)
		return (ft_substr(lst->buff[c], lst->tab[c + 1], ft_strlen(lst->buff[c])));
	else
		return (ft_substr(lst->buff[c], lst->tab[c + 1], ft_s(lst->buff[c], '\n') + 1));
	return (res);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len + start)
		len = ft_strlen(s) - start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}
char	*ft_s(const char *s, int c)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			res = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + ft_strlen((char *)s));
	if (res == 0 && s[0] != (char)c)
		return (NULL);
	return ((char *)s + res);
}
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	

#include <stdio.h>

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