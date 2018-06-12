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

static int	efficiency_of(int *set, int size, int ants, t_path *paths)
{
	int	merge_value;
	int	merge_sum;
	int	in_total;
	int i;

	merge_value = max_len(set, paths) - 1;
	if (merge_value == 1)
		return (1);
	merge_sum = 0;
	i = 0;
	while (i < size)
	{
		merge_sum += merge_value - 
		(get_path_by_id(paths, set[i])->length - 1) + 1;
		i++;
	}
	in_total = merge_value + ft_ceildiv(ants - merge_sum, size);
	return (in_total);
}

static int	set_order(int *arr, int size, int max_p) //TODO: fix it
{
	int i;
	int	mid;

	if (arr[0] > max_p - (size - 1))
		return (false);
	i = 1;
	while (i < size && arr[i] <= max_p - (size - i - 1))
		i++;
	if (i < size)
		mid = ++arr[i - 1];
	while (i < size && mid < max_p)
		arr[i++] = ++mid;
	if (i != size)
		return (false);
	return (true);
}

static int	intersect(int *set, t_path *paths, int rooms_num)
{
	int	rooms[rooms_num];
	int	r;
	int	*path_rooms;

	r = 0;
	while (r < rooms_num)
		rooms[r++] = 0;
	while (*set != -1)
	{
		path_rooms = get_path_by_id(paths, *set)->nodes;
		while (*(path_rooms + 2) != -1)
		{
			path_rooms++;
			if (rooms[*path_rooms])
				return (true);
			else
				rooms[*path_rooms] = 1;
		}
		set++;
	}
	return (false);
}

static int	*pick_some(t_path *paths, int amount, int rooms_num)
{
	int	*cur;
	int	*shortest;
	int	cur_len;
	int	shortest_len;
	int	max_p;
	int	i;
	int TEST_VARIABLE = 0; //DEL

	cur = new_filled_arr(amount);
	max_p = paths->id;
	shortest = NULL;
	shortest_len = INT_MAX;
	while (set_order(cur, amount, max_p))
	{
		i = amount - 1;
		while (cur[i] <= max_p)
		{
			cur_len = len_of_paths(cur, paths);
			if (cur_len < shortest_len && !intersect(cur, paths, rooms_num))
			{
				free(shortest);
				shortest = arr_n_copy(cur, amount);
				if (!shortest)
					break ;
				shortest_len = cur_len;
			}
			cur[i]++;
			TEST_VARIABLE++;
		}
	}
	free(cur);
	ft_printf("found %d variants\n", TEST_VARIABLE);
	return (shortest);
}

int			*get_set(t_path *all_paths, int ants, int rooms_num)
{
	int amount;
	int *best;
	int *cur;
	int	best_ef;
	int	cur_ef;

	best_ef = INT_MAX;
	cur_ef = best_ef - 1;	
	amount = 1;
	cur = NULL;
	best = NULL;
	while (amount <= ants && amount <= all_paths->id + 1 && cur_ef <= best_ef)
	{
		if (!(cur = pick_some(all_paths, amount, rooms_num)))
			break ;
		cur_ef = efficiency_of(cur, amount, ants, all_paths);
		display_set(cur, cur_ef); // DEL
		if (cur_ef < best_ef)
		{
			free(best);
			best_ef = cur_ef;
			best = cur;
		}
		else
			free(cur);
		amount++;
	}
	ft_printf("----------\nBEST SET:\n----------\n"); // DEL
	display_set(best, best_ef); // DEL
	return (best);
}
