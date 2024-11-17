/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:56 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 13:00:15 by tcarlier         ###   ########.fr       */
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

void	*ft_realloc(void *old, size_t oldSz, size_t newSz)
{
	size_t	i;
	char	*new;

	new = malloc(newSz);
	if (!new)
		return (new);
	i = 0;
	while (i < oldSz)
	{
		((char *)new)[i] = ((char *)old)[i];
		++i;
	}
	free(old);
	return (new);
}