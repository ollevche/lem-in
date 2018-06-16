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
		return (-1);
	set_paths[i] = set_paths[i]->prev;
	while (++i < size)
		if (set_paths[i - 1]->prev)
			set_paths[i] = set_paths[i - 1]->prev;
		else
			return (0);
	return (1);
}

static int	place_in_order(t_path **set_paths, t_set *set, int max_p, int is_optimizable);

static void	display_invalid_traversing(t_path **set_paths, int size, int id,
								int partlen, int minlen, int min_leftover)
{
	int i;

	i = 0;
	ft_printf("[size = %d]\t", size);
	while (i < size)
	{
		if (i != id)
			ft_printf("%d ", set_paths[i]->id);
		else
			ft_printf("%dX ", set_paths[i]->id);
		i++;
	}
	ft_printf("\t[part_len (%d) + minlen (%d) >= existing (%d)]\n",
				partlen, minlen, min_leftover);
}

static int	optimize_order(t_path **set_paths, t_set *set, int max_p)
{
	int	i;
	int size;
	int minlen;
	int	partlen;

	if (!set->shortest_path_ever)
		return (0);
	i = 0;
	size = set->size;
	minlen = set->shortest_path_ever->length;
	partlen = 0;
	while (i < size)
	{
		partlen += set_paths[i]->length;
		if (partlen + minlen * (size - 1 - i) >= set->length)
		{
			display_invalid_traversing(set_paths, size, i, partlen, minlen, set->length); // DEL
			partlen -= set_paths[i]->length;
			if (increment_after(i, set_paths, size) < 1)
			{
				ft_printf("place in order after failed increment\n"); // DEL
				return (place_in_order(set_paths, set, max_p, true));
			}
		}
		else
			i++;
	}
	return (0);
}

static int	place_in_order(t_path **set_paths, t_set *set, int max_p,
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
	if (is_optimizable)
		optimize_order(set_paths, set, max_p);
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

static void	display_traversing(t_path **set_paths, int size)
{
	int i;

	i = 0;
	ft_printf("[size = %d]\t", size);
	while (i < size)
	{
		ft_printf("%d ", set_paths[i]->id);
		i++;
	}
	ft_printf("\n");
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
	while (place_in_order(cur, set, paths->id, is_found))
	{
		while (true)
		{
			cur_len = len_of_set_paths(cur);
			if (cur_len < set->length && !intersect(cur, rooms_num))
			{
				free(set->paths);
				set->paths = set_paths_copy(cur, cur_len);
				set->length = cur_len;
				is_found = 1;
			}
			display_traversing(cur, set->size); // DEL
			if (!cur[set->size - 1]->prev)
				break ;
			cur[set->size - 1] = cur[set->size - 1]->prev;
		}
	}
	free(cur);
	return (is_found);
}
