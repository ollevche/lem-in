/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:17:00 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:17:00 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				add_strlist(t_strlist **head, char *str)
{
	t_strlist	*new;

	if (!str)
		return (ERROR_CODE);
	new = (t_strlist*)malloc(sizeof(t_strlist));
	if (!new)
		return (ERROR_CODE);
	new->str = str;
	new->next = *head;
	new->prev = NULL;
	if (*head)
		(*head)->prev = new;
	*head = new;
	return (SUCCESS_CODE);
}

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

int				add_path(t_path **paths, int *nodes)
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
		(*paths)->prev = new;
	new->next = *paths;
	*paths = new;
	return (SUCCESS_CODE);
}

t_path			*get_path_by_id(t_path *paths, int id)
{
	while (paths && paths->id != id)
		paths = paths->next;
	return (paths);
}
