/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 12:27:27 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/01 12:27:28 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_strlist(t_strlist *list)
{
	t_strlist	*trash;

	while (list)
	{
		trash = list;
		list = list->next;
		free(trash->str);
		free(trash);
	}
}

void	free_rooms(t_room *rooms)
{
	t_room	*trash;

	while (rooms)
	{
		trash = rooms;
		rooms = rooms->next;
		free(trash->name);
		free_strlist(trash->comments);
		free(trash->command);
		free(trash);
	}
}

void	free_links(t_link *links)
{
	t_link	*trash;

	while (links)
	{
		trash = links;
		links = links->next;
		free_strlist(trash->comments);
		free(trash);
	}
}
