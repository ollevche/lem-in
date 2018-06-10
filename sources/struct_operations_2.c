/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:29:15 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/07 17:29:17 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path	*get_path_by_id(t_path *paths, int id)
{
	while (paths && paths->id != id)
		paths = paths->next;
	return (paths);
}

int		max_len(int *paths_ids, t_path *paths)
{
	int max_len;
	int	cur_len;
	int	i;

	max_len = 0;
	i = 0;
	while (paths_ids[i] != -1)
	{
		cur_len = get_path_by_id(paths, paths_ids[i])->length;
		if (cur_len > max_len)
			max_len = cur_len;
		i++;
	}
	return (max_len);
}

int		len_of_paths(int *paths_ids, t_path *paths)
{
	int	i;
	int	total_len;

	i = 0;
	total_len = 0;
	while (paths_ids[i] != -1)
	{
		total_len += get_path_by_id(paths, paths_ids[i])->length;
		i++;
	}
	return (total_len);
}

int		*new_filled_arr(int size)
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
