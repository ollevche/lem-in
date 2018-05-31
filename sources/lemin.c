/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:40:08 by ollevche          #+#    #+#             */
/*   Updated: 2018/05/31 12:40:09 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	terminate(t_room *rooms, t_link *links)
{
	(void)rooms;
	(void)links;
}

static void	display_input(int ants, t_room *rooms, t_link *links)
{
	ft_printf("ANTS\n%d\nROOMS\n", ants);
	while (rooms)
	{
		ft_printf("%d: %s, %d, %d\n",
			rooms->id, rooms->name, rooms->x, rooms->y);
		rooms = rooms->next;
	}
	ft_printf("LINKS\n");
	while (links)
	{
		ft_printf("%d-%d\n", links->from, links->to);
		links = links->next;
	}
}

int			main(void)
{
	int		ants;
	t_room	*rooms;
	t_link	*links;

	rooms = NULL;
	links = NULL;
	ants = read_ants();
	read_graph(&rooms, &links);
	if (ants < 1 || !rooms || !links)
		terminate(rooms, links);
	display_input(ants, rooms, links);
	//TODO: an algorithm
	// system("leaks lem-in");
	// global free
	return (0);
}