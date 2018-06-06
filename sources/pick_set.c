/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 10:32:04 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/06 10:32:04 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	get_steps(int *set_paths, t_path *paths, int ants)
{

}

static int	*set_of(int amount, t_path *paths)
{
	int	iterators[amount];
	int	paths_count;
	int	i;

	i = 0;
	while (i < amount)
		iterators[i] = i++;
	paths_count = paths->id + 1;
	
}

static int	*choose_paths(t_paths *paths, int ants)
{
	int		*cur; // an array of current paths (set) ids
	int		*next; // an array of next paths (set) ids
	int		cur_steps;
	int		next_steps;
	int		i;

	cur = NULL;
	next = NULL;
	cur_steps = INT_MAX;
	next_steps = INT_MAX - 1;
	i = 1;
	while (cur_steps > next_steps) // && i <= paths->id + 1 && i < ants) // is any other set worst?
	{
		free(cur);
		cur = next;
		cur_steps = next_steps;
		next = set_of(i, paths);
		if (!next)
		{
			free(cur);
			return (NULL);
		}
		next_steps = get_steps(next, paths, ants);
		i++;
	}
	free(next_set);
	return (cur);
}

t_path		*pick_set(t_paths *all_paths, int ants)
{
	int		*set_paths;
	t_path	*best_set;

	set_paths = choose_paths(all_paths, ants);
	if (!set_paths)
		return (NULL);
	best_set = arr_to_set(paths_of_set, all_paths);
	free(paths_of_set);
	return (best_set);
}