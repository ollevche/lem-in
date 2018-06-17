/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 14:54:12 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/07 14:54:13 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			intersect(t_path **set_paths, int rooms_num)
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

static int	efficiency_of(t_set *set, int ants)
{
	int	merge_value;
	int	merge_sum;
	int	in_total;
	int i;

	merge_value = max_len(set) - 1;
	if (merge_value == 1)
		return (1);
	merge_sum = 0;
	i = 0;
	while (i < set->size)
	{
		set->ants[i] = merge_value - (set->paths[i]->length - 1) + 1;
		merge_sum += set->ants[i++];
	}
	ants = ants - merge_sum + 1;
	in_total = merge_value + ft_ceildiv(ants - 1, set->size);
	i = 0;
	while (i < set->size && --ants > 0)
	{
		set->ants[i]++;
		if (++i == set->size)
			i = 0;
	}
	return (in_total);
}

static int	save_best_set(t_set *cur, t_set *best, int ants)
{
	if (cur->size == 1)
		cur->shortest_path_ever = cur->paths[0];
	free(cur->ants);
	cur->ants = new_arr(cur->size);
	if (!cur->ants)
		return (ERROR_CODE);
	cur->efficiency = efficiency_of(cur, ants);
	display_set("a ", cur);
	if (cur->efficiency < best->efficiency)
	{
		free(best->paths);
		best->size = cur->size;
		best->paths = cur->paths;
		best->length = cur->length;
		best->efficiency = cur->efficiency;
		free(best->ants);
		best->ants = cur->ants;
		cur->ants = NULL;
		best->shortest_path_ever = cur->shortest_path_ever;
	}
	else
		free(cur->paths);
	cur->paths = NULL;
	return (SUCCESS_CODE);
}

t_set		*get_set(t_path *all_paths, int ants, int rooms_num)
{
	t_set	*best;
	t_set	*cur;

	if (!(cur = new_set(1)))
		return (NULL);
	if (!(best = new_set(0)))
	{
		free_set(&cur);
		return (NULL);
	}
	while (cur->size <= ants && cur->size <= all_paths->id + 1)
	{
		cur->efficiency = INT_MAX;
		cur->length = INT_MAX;
		if (pick_set(cur, all_paths, rooms_num) < 1 ||
			save_best_set(cur, best, ants) < 1)
			break ;
		if (cur->efficiency > best->efficiency)
			break ;
		cur->size++;
	}
	free_set(&cur);
	return (best);
}
