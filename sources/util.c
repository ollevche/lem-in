/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:32:15 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/25 18:32:15 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//TODO: test free_*name* functions

void	free_rooms(t_room *room)
{
	t_room *tmp;

	while (room)
	{
		tmp = room;
		room = room->next;
		free(tmp->name);
		free(tmp->comment);
		free(tmp->command);
		free(tmp);
	}
}

void	free_links(t_link *link)
{
	t_link *tmp;

	while (link)
	{
		tmp = link;
		link = link->next;
		free(tmp->comment);
		free(tmp);
	}
}

void	terminate(t_room *room, t_link *link)
{
	free_room(room);
	free_link(link);
	perror("Error");
	exit(EXIT_FAILURE);
}

