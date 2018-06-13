/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operations_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:53:46 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 18:53:48 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	*get_room_by_id(t_room *rooms, int id)
{
	while (rooms && rooms->id != id)
		rooms = rooms->next;
	return (rooms);
}

t_room	*get_room_by_command(t_room *rooms, char *command)
{
	while (rooms)
	{
		if (rooms->command && !ft_strcmp(rooms->command, command))
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

t_room	*get_room_by_name(t_room *rooms, char *name)
{
	while (rooms)
	{
		if (!ft_strcmp(rooms->name, name))
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

int		add_strlist(t_strlist **head, char *str)
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
	ft_printf("new path has been found: id = %d\n", new->id); // DEL
	return (SUCCESS_CODE);
}
