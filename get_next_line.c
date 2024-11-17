/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 17:16:59 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static t_lst    *lst;
    char            *res;
    int             i;
    int             c;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!lst)
        ft_lst_init(&lst, fd);
    c = ft_find_fd(lst, fd);
    while (1)
    {
        i = read(fd, lst->buff[c/2] + lst->tab[c+1], BUFFER_SIZE);
        if (i <= 0) break;
        lst->tab[c+1] += i;
        lst->buff[c/2][lst->tab[c+1]] = '\0';
        if (!ft_new_line(lst->buff[c/2]))
            break;
    }
    if (i < 0 || (lst->tab[c+1] == 0 && !lst->buff[c/2][0]))
        return (NULL);
    return (ft_substr(lst->buff[c/2], 0, 
           ft_s(lst->buff[c/2], '\n') + 1));
}

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char    *res;
    size_t  s_len;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (start >= s_len)
    {
        res = malloc(1);
        if (!res)
            return (NULL);
        res[0] = '\0';
        return (res);
    }
    if (len > s_len - start)
        len = s_len - start;
    res = (char *)malloc(len + 1);
    if (!res)
        return (NULL);
    ft_strlcpy(res, s + start, len + 1);
    if (s[start + len] != '\0')
    {
        ft_strlcpy(s, s + start + len, s_len - (start + len) + 1);
    }
    else
        s[0] = '\0';
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