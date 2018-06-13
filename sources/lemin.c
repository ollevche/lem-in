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

/*
**	TODO: norme errors, start-end paths, display_output()
**	NOT PASSED TESTS: strange_test, 
*/

static void		total_free(t_room **rooms, t_link **links,
						t_strlist **ants_cmnts, int **best_set)
{
	free_rooms(rooms);
	free_links(links);
	free_strlist(ants_cmnts);
	free(*best_set);
	*best_set = NULL;
}

static void		terminate(t_room **rooms, t_link **links,
						t_strlist **ants_cmnts, int **best_set)
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
	if (*ants > 0)
		read_graph(rooms, links);
}

static int		*compose_output(t_room *rooms, t_link *links, int ants)
{
	t_path	*paths;
	int		*best_set;

	paths = get_paths(rooms, links);
	if (!paths)
		return (NULL);
	best_set = get_set(paths, ants, rooms->id + 1);
	free_paths(&paths);
	return (best_set);
}

int				lemin(void)
{
	int			ants;
	t_strlist	*ants_cmnts;
	t_room		*rooms;
	t_link		*links;
	int			*best_set;

	best_set = NULL;
	read_input(&rooms, &links, &ants_cmnts, &ants);
	if (ants < 1 || !rooms || !links)
		terminate(&rooms, &links, &ants_cmnts, &best_set);
	display_input(ants_cmnts, ants, rooms, links);
	best_set = compose_output(rooms, links, ants);
	if (!best_set)
		terminate(&rooms, &links, &ants_cmnts, &best_set);
	// display_output();
	total_free(&rooms, &links, &ants_cmnts, &best_set);
	return (0);
}

int main(void) // DEL
{
	lemin();
	// system("leaks lem-in");
}
