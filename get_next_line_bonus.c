/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/18 00:15:05 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line.c */
#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	static t_gnl	files[1024];
	char			buffer[BUFFER_SIZE + 1];
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
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		files[fd].buf = ft_strjoin_free(files[fd].buf, buffer);
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
