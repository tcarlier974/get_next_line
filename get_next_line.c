/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/22 19:15:45 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line.c */
#include "get_next_line.h"
#include <stdio.h>

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*ft_extract_line(char **str, t_gnl *f)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
		i++;
	line = ft_substr(*str, 0, i);
	tmp = ft_substr(*str, i, ft_strlen(*str) - i);
	free(*str);
	if (!tmp)
	{
		free(line);
		*str = NULL;
		return (NULL);
	}
	*str = tmp;
	if ((*str) == 0)
		free(f);
	return (line);
}

static char	*ft_realloc(char *old, size_t olds, size_t news)
{
	char	*new;
	int		i;

	new = malloc(olds + news + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

static void	ft_find_new(t_gnl *f, ssize_t *bytes, int fd)
{
	int	len;

	if ((*f).eof == 0)
	{
		cleanup_fd(f);
		return ;
	}
	len = ft_strlen((*f).buf);
	while (!ft_strchr((*f).buf, '\n') && *bytes > 0)
	{
		(*f).buf = ft_realloc((*f).buf, ft_strlen((*f).buf), BUFFER_SIZE);
		*bytes = read(fd, (*f).buf + ft_strlen((*f).buf), BUFFER_SIZE);
		if (*bytes > 0)
		{
			(*f).buf[*bytes + len] = '\0';
			len += *bytes;
		}
		else if (*bytes < 0)
		{
			cleanup_fd(f);
			return ;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_gnl	f[1024];
	char			*line;
	ssize_t			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
	{
		return (NULL);
	}
	if (!f[fd].buf)
	{
		f[fd].buf = ft_strdup("");
		f[fd].tab = 0;
		if (!f[fd].eof)
			f[fd].eof = 1;
	}
	line = NULL;
	bytes = 1;
	ft_find_new(&f[fd], &bytes, fd);
	if (f[fd].buf && *f[fd].buf)
		line = ft_extract_line(&f[fd].buf, &f[fd]);
	if (bytes <= 0 || (!f[fd].buf || !*f[fd].buf))
		cleanup_fd(&f[fd]);
	return (line);
}

// int	main(void)
// {
// 	int fd1;
// 	char *line;

// 	fd1 = open("empty.txt", O_RDONLY);
// 	if (fd1 == -1)
// 		return (0);
// 	while (line = get_next_line(fd1))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	free(line);
// 	close(fd1);
// 	free(line);
// 	return (0);
// }
