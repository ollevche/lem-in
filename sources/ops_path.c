/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:10:17 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:10:17 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		add_path(t_path **paths, int *nodes)
{
	t_path	*new;
	int		i;

	new = (t_path*)malloc(sizeof(t_path));
	if (!new)
		return (ERROR_CODE);
	new->id = *paths ? (*paths)->id + 1 : 0;
	new->nodes = nodes;
	i = 0;
	while (nodes[i] != -1)
		i++;
	new->length = i;
	new->next = *paths;
	*paths = new;
	return (SUCCESS_CODE);
}

t_path	*get_path_by_id(t_path *paths, int id)
{
	while (paths && paths->id != id)
		paths = paths->next;
	return (paths);
}

int		len_of_paths(int *paths_ids, t_path *paths) // it's "set" function
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

int		max_len(int *paths_ids, t_path *paths) // it's "set" function
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
