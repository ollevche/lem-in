/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:54:30 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 12:54:31 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	**empty_matrix(int size)
{
	int	**matrix;
	int	i;
	int j;

	matrix = (int**)malloc(sizeof(int*) * (size + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < size)
	{
		matrix[i] = (int*)malloc(sizeof(int) * (size));
		if (!matrix[i])
			break ;
		j = 0;
		while (j < size)
			matrix[i][j++] = 0;
		i++;
	}
	matrix[size] = NULL;
	if (i != size)
		free_matrix(&matrix);
	return (matrix);
}

int			**compose_matrix(t_room *rooms, t_link *links)
{
	int	**matrix;

	matrix = empty_matrix(rooms->id + 1);
	if (!matrix)
		return (NULL);
	while (links)
	{
		matrix[links->from][links->to] = 1;
		matrix[links->to][links->from] = 1;
		links = links->next;
	}
	// display_matrix(matrix, rooms->id + 1);
	return (matrix);
}