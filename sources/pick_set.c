/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:02:24 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/15 16:02:24 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	place_in_order(t_path **set_paths, int size, int max_p)
{
	int i;

	i = size - 1;
	while (i > -1 && set_paths[i]->id >= max_p - (size - i - 1))
		i--;
	if (i < 0)
		return (false);
	if (i + 1 < size)
		set_paths[i] = set_paths[i]->prev;
	while (++i < size)
		set_paths[i] = set_paths[i - 1]->prev;
	return (true);
}

static int	intersect(t_path **set_paths, int rooms_num)
{
	int	rooms[rooms_num];
	int	*path_rooms;
	int	r;
	int p;

	r = 0;
	while (r < rooms_num)
		rooms[r++] = 0;
	p = 0;
	while (set_paths[p])
	{
		path_rooms = set_paths[p]->nodes;
		while (*(path_rooms + 2) != -1)
		{
			path_rooms++;
			if (rooms[*path_rooms])
				return (true);
			else
				rooms[*path_rooms] = 1;
		}
		p++;
	}
	return (false);
}

int			pick_set(t_set *set, t_path *paths, int rooms_num)
{
	t_path	**cur;
	int		cur_len;
	int		is_found;

	cur = new_set_paths(set->size, paths);
	if (!cur)
		return (-1);
	is_found = 0;
	while (place_in_order(cur, set->size, paths->id))
	{
		while (cur[set->size - 1]->prev)
		{
			cur_len = len_of_set_paths(cur);
			if (cur_len < set->length && !intersect(cur, rooms_num))
			{
				free(set->paths);
				set->paths = set_paths_copy(cur, cur_len);
				set->length = cur_len;
				is_found = 1;
			}
			cur[set->size - 1] = cur[set->size - 1]->prev;
		}
	}
	free(cur);
	return (is_found);
}
