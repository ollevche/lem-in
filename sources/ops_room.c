/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:14:19 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:14:19 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	new_elem->x = ft_atoi(line + i++);
	while (line[i] && line[i] != ' ')
		i++;
	new_elem->y = ft_atoi(line + i);
	new_elem->comments = *comments;
	new_elem->command = *command;
	*comments = NULL;
	*command = NULL;
	if (get_room_by_command(new_elem->next, new_elem->command))
		return (ERROR_CODE);
	if (get_room_by_name(new_elem->next, new_elem->name))
		return (ERROR_CODE);
	return (SUCCESS_CODE);
}

t_room			*get_room_by_id(t_room *rooms, int id)
{
	while (rooms && rooms->id != id)
		rooms = rooms->next;
	return (rooms);
}

t_room			*get_room_by_command(t_room *rooms, char *command)
{
	while (rooms)
	{
		if (rooms->command && !ft_strcmp(rooms->command, command))
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

t_room			*get_room_by_name(t_room *rooms, char *name)
{
	while (rooms)
	{
		if (!ft_strcmp(rooms->name, name))
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}
