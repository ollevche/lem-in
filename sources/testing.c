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

void	display_matrix(int **matrix)
{
	int i;
	int j;

	i = 0;
	while (matrix[i])
	{
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

void	print_arr(int *arr)
{
	while (*arr != -1)
	{
		ft_printf("%d", *arr);
		arr++;
		if (*arr != -1)
			ft_printf("-");
	}
}

void	display_paths(t_path *paths)
{
	while (paths)
	{
		ft_printf("path_%d (%d):\t", paths->id, paths->length);
		print_arr(paths->nodes);
		ft_printf("\n");
		paths = paths->next;
	}
}