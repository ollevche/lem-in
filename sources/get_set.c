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

int			max_len(t_set *set) // TODO: test it
{
	int max_len;
	int	cur_len;
	int	i;

	max_len = 0;
	i = 0;
	while (set->paths[i])
	{
		cur_len = set->paths[i]->length;
		if (cur_len > max_len)
			max_len = cur_len;
		i++;
	}
	return (max_len);
}

static int	efficiency_of(t_set *set, int ants) // TODO: test it
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
		merge_sum += merge_value - (set->paths[i]->length - 1) + 1;
		i++;
	}
	in_total = merge_value + ft_ceildiv(ants - merge_sum, set->size);
	return (in_total);
}

static int	set_order(t_path **set_paths, int size, int max_p)
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

t_path		**new_set_paths(int size, t_path *paths) // TODO: test it
{
	t_path	**new;
	int		i;

	new = (t_path**)malloc(sizeof(t_path*) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = get_path_by_id(paths, i);
		i++;
	}
	new[i] = NULL;
	return (new);
}

t_path		**set_paths_copy(t_path **set_paths, int size) // TODO: test it
{
	t_path	**copy;
	int		i;

	copy = (t_path**)malloc(sizeof(t_path*) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = set_paths[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int			len_of_set_paths(t_path **set_paths) // TODO: test it
{
	int	i;
	int	total_len;

	i = 0;
	total_len = 0;
	while (set_paths[i])
	{
		total_len += set_paths[i]->length;
		i++;
	}
	return (total_len);
}

static int	pick_set(t_set *set, t_path *paths, int rooms_num)
{
	t_path	**cur;
	int		cur_len;
	int		max_p;
	int		i;
	int		is_found;

	cur = new_set_paths(set->size, paths);
	if (!cur)
		return (-1);
	max_p = paths->id;
	is_found = 0;
	while (set_order(cur, set->size, max_p))
	{
		i = set->size - 1;
		while (cur[i]->prev)
		{
			cur_len = len_of_set_paths(cur);
			if (cur_len < set->length && !intersect(cur, rooms_num))
			{
				free(set->paths);
				set->paths = set_paths_copy(cur, cur_len);
				set->length = cur_len;
				is_found = 1;
			}
			cur[i] = cur[i]->prev;
		}
	}
	free(cur);
	return (is_found);
}

static void	save_best_set(t_set *cur, t_set *best, int ants)
{
	cur->efficiency = efficiency_of(cur, ants);
	if (cur->efficiency < best->efficiency)
	{
		free(best->paths);
		best->size = cur->size;
		best->paths = cur->paths;
		display_set(cur); // DEL
		cur->paths = NULL;
		best->length = cur->length;
		best->efficiency = cur->efficiency;
	}
	else
		free(cur->paths);
}

t_set		*new_set(int size) // TODO: test it
{
	t_set *new;

	new = (t_set*)malloc(sizeof(t_set));
	if (!new)
		return (NULL);
	new->size = size;
	new->paths = NULL;
	new->length = INT_MAX;
	new->efficiency = INT_MAX;
	return (new);
}

void		set_reset(t_set *set)
{
	set->efficiency = INT_MAX;
	set->length = INT_MAX;
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
		set_reset(cur);
		if (pick_set(cur, all_paths, rooms_num) < 1)
			break ;
		save_best_set(cur, best, ants);
		// if (cur->efficiency > best->efficiency) // TODO: test it
		// 	break ;
		cur->size++;
	}
	return (best);
}
