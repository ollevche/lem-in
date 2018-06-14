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
	new->prev = NULL;
	if (*paths)
		(*paths)->prev = new; // TODO: test it
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
