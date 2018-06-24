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

int			optimize_order(t_path **set_paths, t_set *set, int max_p)
{
	int	i;
	int size;
	int minlen;
	int	partlen;

	i = 0;
	size = set->size;
	minlen = set->shortest_path_ever->length;
	partlen = 0;
	while (i < size)
	{
		partlen += set_paths[i]->length;
		if (partlen + minlen * (size - 1 - i) >= set->length)
		{
			partlen -= set_paths[i]->length;
			display_invalid_traversing(set_paths, size, i);
			if (increment_after(i, set_paths, size) < 1)
				return (place_in_order(set_paths, set, max_p, true));
		}
		else
			i++;
	}
	return (true);
}

int			place_in_order(t_path **set_paths, t_set *set, int max_p,
							int is_optimizable)
{
	int i;
	int size;

	size = set->size;
	i = size - 1;
	while (i > -1 && set_paths[i]->id >= max_p - (size - i - 1))
		i--;
	if (i < 0)
		return (false);
	if (i + 1 < size)
		increment_after(i, set_paths, size);
	if (g_smart && is_optimizable)
		return (optimize_order(set_paths, set, max_p));
	return (true);
}

static int	save_best(t_set *set, t_path **set_paths, int set_len)
{
	free(set->paths);
	set->paths = set_paths_copy(set_paths, set_len);
	if (!set->paths)
		return (ERROR_CODE);
	set->length = set_len;
	return (SUCCESS_CODE);
}

static int	distinct(t_path **set_paths, t_set *set, int max_p, int isfound)
{
	int	id;
	int	is_dis;

	is_dis = false;
	while (!is_dis)
	{
		id = intersect(set_paths, set->total_rooms);
		if (!id)
			is_dis = true;
		else if (increment_after(id, set_paths, set->size) < 1 &&
				!place_in_order(set_paths, set, max_p, isfound))
			break ;
	}
	return (is_dis);
}

int			pick_set(t_set *set, t_path *paths)
{
	t_path	**cur;
	int		cur_len;
	int		isfound;

	if (!(cur = new_set_paths(set->size, paths)))
		return (ERROR_CODE);
	isfound = 0;
	if (paths->id == set->size - 1)
		isfound = save_best(set, cur, set->size);
	while (place_in_order(cur, set, paths->id, isfound) &&
			distinct(cur, set, paths->id, isfound) && isfound != ERROR_CODE)
	{
		while (true)
		{
			cur_len = len_of_set_paths(cur);
			if (cur_len < set->length)// && !intersect(cur, set->total_rooms))
				isfound = save_best(set, cur, cur_len);
			display_traversing(cur, set->size);
			if (!cur[set->size - 1]->prev || isfound == ERROR_CODE)
				break ;
			cur[set->size - 1] = cur[set->size - 1]->prev;
		}
	}
	free(cur);
	return (isfound);
}
