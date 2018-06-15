/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:58:33 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/15 15:58:34 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		max_len(t_set *set)
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

t_path	**new_set_paths(int size, t_path *paths)
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

t_path	**set_paths_copy(t_path **set_paths, int size)
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

int		len_of_set_paths(t_path **set_paths)
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

t_set	*new_set(int size)
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
