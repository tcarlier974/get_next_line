/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:56 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 13:05:09 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lst_init(int **lst, int fd)
{
	*lst = (int *)malloc(sizeof(int) * 3);
	*lst[0] = fd;
	*lst[1] = 0;
	*lst[3] = -1;
}

void	*ft_realloc(void *buff, size_t olds, size_t news)
{
	size_t	i;
	char	*new;

	new = malloc(news);
	if (!new)
		return (new);
	i = 0;
	while (i < olds)
	{
		((char *)new)[i] = ((char *)buff)[i];
		++i;
	}
	free(buff);
	return (new);
}