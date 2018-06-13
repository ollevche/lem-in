/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 13:32:04 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 13:32:05 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		display_matrix(int **matrix)
{
	int i;
	int j;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		if (!matrix[i])
			return ;
		j = 0;
		while (matrix[i][j] != -1)
		{
			ft_printf("%d\t", matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

static void	print_path(int *arr, t_room *rooms)
{
	if (!arr || !rooms)
		return ;
	while (*arr != -1)
	{
		ft_printf("%s", get_room_by_id(rooms, *arr)->name);
		arr++;
		if (*arr != -1)
			ft_printf("-");
	}
}

void		display_paths(t_path *paths, t_room *rooms)
{
	if (!rooms)
		return ;
	while (paths)
	{
		ft_printf("path_%d\t(%d):\t", paths->id, paths->length);
		print_path(paths->nodes, rooms);
		ft_printf("\n");
		paths = paths->next;
	}
}

void		display_set(int *set, int efficiency)
{
	int i;

	if (!set)
		return ;
	i = 0;
	ft_printf("some set (paths ids):\t");
	while (set[i] != -1)
	{
		ft_printf("%d\t", set[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("size = %d\n", i);
	ft_printf("efficiency = %d\n", efficiency);
}
