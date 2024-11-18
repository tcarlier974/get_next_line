/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/18 12:40:26 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line.c */
#include "get_next_line_bonus.h"

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

static char	*ft_extract_line(char **str)
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
	*str = tmp;
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

char	*get_next_line(int fd)
{
	static t_gnl	files[1024];
	char			*line;
	ssize_t			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
	{
		return (NULL);
	}
	if (!files[fd].buf)
		files[fd].buf = ft_strdup("");
	line = NULL;
	while (!ft_strchr(files[fd].buf, '\n'))
	{
		files[fd].buf = ft_realloc(files[fd].buf, ft_strlen(files[fd].buf), BUFFER_SIZE);
		bytes = read(fd, files[fd].buf + files[fd].tab[fd], BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		files[fd].buf[files[fd].tab[fd] + bytes] = '\0';
		files[fd].tab[fd] += bytes;
	}
	if (files[fd].buf && *files[fd].buf)
		line = ft_extract_line(&files[fd].buf);
	return (line);
}

// int	main(void)
// {
// 	int fd1;
// 	char *line;

// 	fd1 = open("test.txt", O_RDONLY);
// 	int fd2 = open("test2.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1)
// 		return (0);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }
