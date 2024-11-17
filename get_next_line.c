/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:54 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 13:36:09 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_lst	*lst;
	char			*res;
	t_lst			*lst_tmp;
	int				i;
	int				c;
	
	if (fd == 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!lst)
		ft_lst_init(lst, fd);
	c = ft_find_fd(lst, fd);
	i = -1;
	while(!(ft_new_line(lst->buff)) || i == 0);
	{
		ft_realloc(lst->buff, ft_strlen(lst_tmp->buff),
			ft_strlen(lst->buff) + BUFFER_SIZE);
		i = read(fd, lst->buff + lst->tab[c + 1], BUFFER_SIZE);
	}
	
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