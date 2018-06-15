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
		merge_sum += merge_value - (set->paths[i]->length - 1) + 1;
		i++;
	}
	in_total = merge_value + ft_ceildiv(ants - merge_sum, set->size);
	return (in_total);
}

static void	save_best_set(t_set *cur, t_set *best, int ants)
{
	cur->efficiency = efficiency_of(cur, ants);
	if (cur->efficiency < best->efficiency)
	{
		free(best->paths);
		best->size = cur->size;
		best->paths = cur->paths;
		display_set("", cur); // DEL
		cur->paths = NULL;
		best->length = cur->length;
		best->efficiency = cur->efficiency;
	}
	else
		free(cur->paths);
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
		if (pick_set(cur, all_paths, rooms_num) < 1)
			break ;
		save_best_set(cur, best, ants);
		if (cur->efficiency > best->efficiency) // TODO: test it
			break ;
		cur->size++;
	}
	return (best);
}
