/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:54:29 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 16:54:31 by ollevche         ###   ########.fr       */
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
	// display_matrix(matrix, rooms->id + 1);
	return (matrix);
}

//bfs(int **matrix, int *cur_path, int end, t_paths **paths)

t_path		*find_paths(t_room *rooms, t_link *links)
{
	t_path	*paths;
	int		**matrix;
	int		*cur_path;
	int		end_room;
	int		i;

	matrix = compose_matrix(rooms, links);
	if (!matrix)
		return (NULL);
	cur_path = (int*)malloc(sizeof(int) * (rooms->id + 2));
	if (!cur_path)
	{
		free_matrix(matrix);
		return(NULL);
	}
	i = 0;
	while (i < rooms->id + 2)
		cur_path[i++] = -1;
	cur_path[0] = get_room_by_command(rooms, "##start")->id;
	end_room = get_room_by_command(rooms, "##end")->id;
	paths = bfsearch(matrix, cur_path, end_room, NULL);
	free_matrix(&matrix);
	return(paths);
}
