/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:56 by tcarlier          #+#    #+#             */
/*   Updated: 2024/11/17 13:40:01 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lst_init(t_lst *lst, int fd)
{
	lst->tab = (int *)malloc(sizeof(int) * 3);
	lst->tab[0] = fd;
	lst->tab[1] = 0;
	lst->tab[2] = -1;
}

void	ft_lst_add_back(t_lst *lst, int fd)
{
	int	i;

	i = 0;
	while (lst->tab[i] != -1)
	{
		i++;
	}
	ft_realloc_int(lst->tab, i + 1, i + 3);
	lst->tab[i] = fd;
	lst->tab[i + 1] = 0;
	lst->tab[i + 2] = -1;
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

void	*ft_realloc_int(void *buff, size_t olds, size_t news)
{
	size_t	i;
	char	*new;

	new = malloc(sizeof(int) * news);
	if (!new)
		return (new);
	i = 0;
	while (i < olds)
	{
		((int *)new)[i] = ((int *)buff)[i];
		++i;
	}
	free(buff);
	return (new);
}

int		ft_find_fd(t_lst *lst, int fd)
{
	int	i;

	i = 0;
	while (lst->tab[i] != fd)
		i += 2;
	if (lst->tab[i] == -1)
		ft_lst_add_back(lst, fd);
	return (i);
}