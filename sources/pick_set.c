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

static int	increment_after(int i, t_path **set_paths, int size)
{
	if (!set_paths[i]->prev)
		return (ERROR_CODE);
	set_paths[i] = set_paths[i]->prev;
	while (++i < size)
		if (set_paths[i - 1]->prev)
			set_paths[i] = set_paths[i - 1]->prev;
		else
			return (false);
	return (true);
}

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

int			pick_set(t_set *set, t_path *paths, int rooms_num)
{
	t_path	**cur;
	int		cur_len;
	int		is_found;

	if (!(cur = new_set_paths(set->size, paths)))
		return (ERROR_CODE);
	is_found = 0;
	if (!paths->id && set->size == 1)
		is_found = save_best(set, cur, set->size);
	while (place_in_order(cur, set, paths->id, is_found) &&
			is_found != ERROR_CODE)
	{
		while (true)
		{
			cur_len = len_of_set_paths(cur);
			if (cur_len < set->length && !intersect(cur, rooms_num))
				is_found = save_best(set, cur, cur_len);
			display_traversing(cur, set->size);
			if (!cur[set->size - 1]->prev || is_found == ERROR_CODE)
				break ;
			cur[set->size - 1] = cur[set->size - 1]->prev;
		}
	}
	free(cur);
	return (is_found);
}
