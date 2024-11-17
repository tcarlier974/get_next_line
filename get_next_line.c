/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 12:58:00 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	*lst;
	char		*str;
	int			i;
	char		*buff;
	
	if (fd == 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!lst)
		ft_lst_init(&lst, fd);
	buff = "";
	while(!(ft_new_line(buff)));
	{
		
		i = read(fd, buff, BUFFER_SIZE);
	}
	ft_find_fd(&i);
}
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