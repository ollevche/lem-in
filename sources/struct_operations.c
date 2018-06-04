/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:41:26 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 12:41:27 by ollevche         ###   ########.fr       */
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
		if (rooms->command && ft_strcmp(rooms->command, command))
			break ;
		rooms = rooms->next;
	}
	return (rooms);
}

int		add_strlist(t_strlist **head, char *str)
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
