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

static void		total_free(t_room **rooms, t_link **links,
						t_strlist **ants_cmnts, t_path **best_set)
{
	free_rooms(rooms);
	free_links(links);
	free_strlist(ants_cmnts);
	free_paths(best_set);
}

static void		terminate(t_room **rooms, t_link **links,
						t_strlist **ants_cmnts, t_path **best_set)
{
	if (errno)
		perror("Error");
	else
		ft_printf("ERROR\n");
	total_free(rooms, links, ants_cmnts, best_set);
	exit(EXIT_FAILURE);
}

static void		read_input(t_room **rooms, t_link **links,
						t_strlist **ants_comments, int *ants)
{
	*rooms = NULL;
	*links = NULL;
	*ants_comments = NULL;
	*ants = read_ants(ants_comments);
	read_graph(rooms, links);
}

static t_path	*compose_output(t_room *rooms, t_link *links, int ants) //TODO: this
{
	t_path	*paths;

	paths = get_paths(rooms, links);
	if (!paths)
		return (NULL);
	(void)rooms;
	(void)links;
	(void)ants;
	return (NULL);
}

int				main(void)
{
	int			ants;
	t_strlist	*ants_cmnts;
	t_room		*rooms;
	t_link		*links;
	t_path		*best_set;

	read_input(&rooms, &links, &ants_cmnts, &ants);
	if (ants < 1 || !rooms || !links)
		terminate(&rooms, &links, &ants_cmnts, NULL);
	display_input(ants_cmnts, ants, rooms, links);
	best_set = compose_output(rooms, links, ants);
	if (!best_set)
		terminate(&rooms, &links, &ants_cmnts, &best_set);
	// display_output();
	total_free(&rooms, &links, &ants_cmnts, &best_set);
	system("leaks lem-in"); // DEL
	return (0);
}
