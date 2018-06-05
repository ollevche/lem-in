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

static void	totally_free(t_room **rooms, t_link **links,
						t_path **paths, t_path **best_set)
{
	free_rooms(rooms);
	free_links(links);
	free_paths(paths);
	free_paths(best_set);
}

static void	terminate(t_room *rooms, t_link *links,
						t_path *paths, t_path *best_set)
{
	if (errno)
		perror("Error");
	else
		ft_printf("ERROR\n");
	totally_free(&rooms, &links, &paths, &best_set);
	exit(EXIT_FAILURE);
}

int			main(void)
{
	int		ants;
	t_room	*rooms;
	t_link	*links;
	t_path	*paths;
	t_path	*best_set;

	rooms = NULL;
	links = NULL;
	ants = read_ants();
	read_graph(&rooms, &links);
	if (ants < 1 || !rooms || !links)
		terminate(rooms, links, NULL, NULL);
	display_input(ants, rooms, links);
	paths = find_paths(rooms, links); // finds all paths using matrix
	if (!paths)
		terminate(rooms, links, paths, NULL);		
	// best_set = pick_set(paths, ants); // composes best possible set of paths
	// if (!best_set)
		// terminate(rooms, links, paths, best_set);
	// display_output(best_set, paths); // prints output data
	best_set = NULL;//DEL
	totally_free(&rooms, &links, &paths, &best_set);
	// system("leaks lem-in");
	return (0);
}
