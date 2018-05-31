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

void	terminate(t_room *rooms, t_link *links)
{
	(void)rooms;
	(void)links;
}

void	display_input(int ants, t_room *rooms, t_link *links)
{
	ft_printf("%d\n", ants);
	(void)rooms;
	(void)links;
}

int	main(void)
{
	int		ants;
	t_room	*rooms;
	t_link	*links;

	ants = read_ants();
	rooms = read_rooms();
	links = read_links();
	if (ants < 1 || !rooms || !links)
		terminate(rooms, links);
	display_input(ants, rooms, links);
	//TODO: an algorithm
	// system("leaks lem-in");
	return (0);
}