/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 14:40:53 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/07 14:40:54 by ollevche         ###   ########.fr       */
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
		matrix[i] = (int*)malloc(sizeof(int) * (size + 1));
		if (!matrix[i])
			break ;
		matrix[i][size] = -1;
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

static int	**compose_matrix(t_room *rooms, t_link *links)
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
	return (matrix);
}

static int	search(int **matrix, int *nodes, int end, t_path **paths)
{
	int	cur_node;
	int	ret_code;
	int	*nodes_copy;
	int	i;

	cur_node = arr_get_last_elem(nodes);
	ret_code = SUCCESS_CODE;
	if (cur_node == end)
		return (add_path(paths, nodes));
	i = 0;
	while (matrix[cur_node][i] != -1)
	{
		if (matrix[cur_node][i] == 1 && !arr_contains(nodes, i))
		{
			nodes_copy = arr_extend(nodes, i);
			if (!nodes_copy)
				break ;
			ret_code = search(matrix, nodes_copy, end, paths);
			if (ret_code == ERROR_CODE)
				break ;
		}
		i++;
	}
	free(nodes);
	return (ret_code);
}

/*
**	it's too hard to make beautiful function normed
**	a lot of weird assignations here
*/

t_path		*get_paths(t_room *rooms, t_link *links)
{
	t_path	*paths;
	int		**matrix;
	int		*nodes;
	int		end_room;
	t_room	*tmp_room;

	if (!(matrix = compose_matrix(rooms, links)))
		return (NULL);
	if (!(tmp_room = get_room_by_command(rooms, "##start"))
		|| !(nodes = to_arr(tmp_room->id)))
	{
		free_matrix(&matrix);
		return (NULL);
	}
	end_room = -1;
	if ((tmp_room = get_room_by_command(rooms, "##end")))
		end_room = tmp_room->id;
	if ((paths = NULL) || end_room == -1 || nodes[0] == -1 ||
		search(matrix, nodes, end_room, &paths) == ERROR_CODE)
	{
		free(nodes);
		free_paths(&paths);
	}
	free_matrix(&matrix);
	return (paths);
}
