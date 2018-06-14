/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:15:03 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:15:04 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_link	*new_link(t_link **links)
{
	t_link	*new_elem;

	new_elem = (t_link*)malloc(sizeof(t_link));
	if (!new_elem)
		return (NULL);
	new_elem->next = *links;
	new_elem->prev = NULL;
	if (*links)
		(*links)->prev = new_elem;
	*links = new_elem;
	return (new_elem);
}

int				add_link(t_link **links, t_room *rooms, char *line,
					t_strlist **comments)
{
	t_link	*new_elem;
	t_room	*room_iter;
	int		i;

	new_elem = new_link(links);
	if (!new_elem)
		return (operation_failure(*comments, NULL));
	new_elem->comments = *comments;
	*comments = NULL;
	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	room_iter = rooms;
	while (ft_strlen(room_iter->name) != (size_t)i
			|| ft_strncmp(line, room_iter->name, i))
		room_iter = room_iter->next;
	new_elem->from = room_iter->id;
	room_iter = rooms;
	while (ft_strcmp(line + i + 1, room_iter->name))
		room_iter = room_iter->next;
	new_elem->to = room_iter->id;
	return (SUCCESS_CODE);
}
