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

#include "lemin.h" // TODO: 2d array with ids, lengths and ants number (is it new struct?); intersection; array of pointers

static int	efficiency_of(int *set_paths, int size, int ants, t_path *all_paths)
{
	int	merge_value;
	int	merge_sum;
	int	in_total;
	int i;

	merge_value = max_len(set_paths, all_paths) - 1;
	merge_sum = 0;
	i = 0;
	while (i < size)
	{
		merge_sum += merge_value - 
		(get_path_by_id(all_paths, set_paths[i])->length - 1) + 1;
		i++;
	}
	in_total = merge_value + ft_ceildiv(ants - merge_sum, size);
	return (in_total);
}

static int	set_order(int *cur, int size, int max_p) // TODO: rename cur (arr)
{
	int i;
	int	mid;

	if (cur[0] > max_p - (size - 1))
		return (false);
	i = 1;
	while (i < size && cur[i] <= i)
		i++;
	if (i < size)
		mid = ++cur[i - 1];
	while (i < size && mid < max_p)
		cur[i++] = ++mid;
	if (i != size)
		return (false);
	return (true);
}

static int	*new_filled_arr(int size)
{
	int	*arr;
	int i;

	arr = (int*)malloc(sizeof(int) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = i;
		i++;
	}
	arr[size] = -1;
	return (arr);
}

static int	*pick_some(t_path *paths, int amount)
{
	int	*cur;
	int	*shortest;
	int	cur_len;
	int	shortest_len;
	int	max_p;
	int	i;

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
			if (cur_len < shortest_len)
			{
				free(shortest);
				shortest = arr_n_copy(cur, amount);
				if (!shortest)
					break ;
				shortest_len = cur_len;
			}
			cur[i]++;
		}
	}
	free(cur);
	return (shortest);
}

int			*get_set(t_path *all_paths, int ants)
{
	int amount;
	int *best;
	int *cur;
	int	best_ef;
	int	cur_ef;

	best_ef = INT_MAX;
	amount = 1;
	cur = NULL;
	best = NULL;
	while (amount <= ants && amount <= all_paths->id + 1 && cur_ef <= best_ef)
	{
		cur = pick_some(all_paths, amount); // error
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
	ft_printf("BEST SET:\n"); // DEL
	display_set(best, best_ef); // DEL
	return (best);
}

/*
	int	amount;
	int	*cur;
	int	*next;
	int	cur_ef;
	int	next_ef;

	amount = 1;
	cur = NULL;
	next = NULL;
	cur_ef = INT_MAX;
	next_ef = cur_ef - 1;
	while (amount <= all_paths->id + 1 && amount <= ants)
	{
		if (!(next = pick_some(all_paths, amount)))
		{
			ft_memdel((void**)&cur);
			break ;
		}
		next_ef = efficiency_of(next, amount, ants, all_paths);
		if (cur_ef < next_ef) // or '<=' ?
			break ;
		free(cur);
		cur = next;
		cur_ef = next_ef;
		amount++;
		display_set(next, next_ef); // DEL
	}
	if (amount < all_paths->id + 1)
		free(next);
	display_set(cur, cur_ef); // DEL
	return (cur);
*/
