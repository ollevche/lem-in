/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:20:49 by ollevche          #+#    #+#             */
/*   Updated: 2018/05/31 17:20:49 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room		*get_room(t_room *rooms, int id)
{
	while (rooms && rooms->id != id)
		rooms = rooms->next;
	return (rooms);
}

int			add_strlist(t_strlist **head, char *str)
{
	t_strlist	*new_elem;

	new_elem = (t_strlist*)malloc(sizeof(t_strlist));
	if (!new_elem)
		return (ERROR_CODE);
	new_elem->str = str;
	new_elem->next = *head;
	new_elem->prev = NULL;
	if (*head)
		(*head)->prev = new_elem;
	*head = new_elem;
	return (SUCCESS_CODE);
}

//TODO: rewrite add_room() and add_link() functions

static int	add_crashes(t_strlist *comments, char *command)
{
	free_strlist(comments);
	free(command);
	return (ERROR_CODE);
}

int			add_room(t_room **rooms, char *line,
					t_strlist **comments, char **command)
{
	t_room	*new_elem;
	int		i;

	new_elem = (t_room*)malloc(sizeof(t_room));
	if (!new_elem)
		return (add_crashes(*comments, *command));
	new_elem->id = *rooms ? (*rooms)->id + 1 : 0;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	new_elem->name = ft_strndup(line, i);
	new_elem->x = ft_atoi(line + i);
	while (line[i] && line[i] != ' ')
		i++;
	new_elem->y = ft_atoi(line + i);
	new_elem->comments = *comments;
	new_elem->command = *command;
	*comments = NULL;
	*command = NULL;
	new_elem->next = *rooms;
	new_elem->prev = NULL;
	(*rooms) ? (*rooms)->prev = new_elem : 0;
	*rooms = new_elem;
	if (!new_elem->name)
		return (ERROR_CODE);
	return (SUCCESS_CODE);
}

int			add_link(t_link **links, t_room *rooms, char *line,
					t_strlist **comments)
{
	t_link	*new_elem;
	t_room	*room_iter;
	int		i;

	new_elem = (t_link*)malloc(sizeof(t_link));
	if (!new_elem)
		return (add_crashes(*comments, NULL));
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
	new_elem->next = *links;
	new_elem->prev = NULL;
	if (*links)
		(*links)->prev = new_elem;
	*links = new_elem;
	return (SUCCESS_CODE);
}
