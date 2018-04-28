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

void	free_room(t_room *room)
{
	t_room tmp;

	while (room)
	{
		tmp = room;
		room = room->next;
		free(tmp->name);
		free(tmp);
	}
}

void	free_link(t_link *link)
{
	t_link *tmp;

	while (link)
	{
		tmp = link;
		link = link->next;
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

