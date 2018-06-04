/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_room_or_link.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:40:57 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 12:40:58 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		operation_failure(t_strlist *comments, char *command)
{
	free_strlist(&comments);
	free(command);
	return (ERROR_CODE);
}

static t_room	*new_room(t_room **rooms)
{
	t_room	*new;

	new = (t_room*)malloc(sizeof(t_room));
	if (!new)
		return (NULL);
	new->id = *rooms ? (*rooms)->id + 1 : 0;
	new->next = *rooms;
	new->prev = NULL;
	if (*rooms)
		(*rooms)->prev = new;
	*rooms = new;
	return (new);
}

int				add_room(t_room **rooms, char *line,
					t_strlist **comments, char **command)
{
	t_room	*new_elem;
	int		i;

	new_elem = new_room(rooms);
	if (!new_elem)
		return (operation_failure(*comments, *command));
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	new_elem->name = ft_strndup(line, i);
	if (!new_elem->name)
		return (ERROR_CODE);
	new_elem->x = ft_atoi(line + i);
	while (line[i] && line[i] != ' ')
		i++;
	new_elem->y = ft_atoi(line + i);
	new_elem->comments = *comments;
	new_elem->command = *command;
	*comments = NULL;
	*command = NULL;
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
	while (ft_strncmp(line, room_iter->name, i))
		room_iter = room_iter->next;
	new_elem->from = room_iter->id;
	room_iter = rooms;
	while (ft_strcmp(line + i + 1, room_iter->name))
		room_iter = room_iter->next;
	new_elem->to = room_iter->id;
	return (SUCCESS_CODE);
}
