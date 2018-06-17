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
**	TODO: norme errors;
**	'-quick' combines sets without traversing;
**	'-maxset NUM' - sets max number of paths in a set;
**	display_output(); start-end paths;
*/

int g_log = 0;
int g_smart = 1;

static t_set	*compose_output(t_room *rooms, t_link *links, int ants)
{
	t_path	*paths;
	t_set	*set;

	paths = get_paths(rooms, links);
	if (!paths)
		return (NULL);
	display_paths("all of paths:\n", paths, rooms);
	set = get_set(paths, ants, rooms->id + 1);
	display_set("best:\n", set);
	free_paths(&paths);
	return (set);
}

static int		lemin(void)
{
	int			ants;
	t_strlist	*ants_cmnts;
	t_room		*rooms;
	t_link		*links;
	t_set		*set;

	set = NULL;
	rooms = NULL;
	links = NULL;
	ants_cmnts = NULL;
	ants = read_ants(&ants_cmnts);
	if (ants > 0)
		read_graph(&rooms, &links);
	if (ants < 1 || !rooms || !links)
		terminate(&rooms, &links, &ants_cmnts, &set);
	set = compose_output(rooms, links, ants);
	if (!set)
		terminate(&rooms, &links, &ants_cmnts, &set);
	if (!g_log)
		display_input(ants_cmnts, ants, rooms, links);
	// display_output();
	total_free(&rooms, &links, &ants_cmnts, &set);
	return (0);
}

static void		set_params(int argc, char **args)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!g_log && !ft_strcmp(args[i], "-log"))
			g_log = 1;
		else if (!ft_strcmp(args[i - 1], "-log")
				&& !ft_strcmp(args[i], "--t"))
			g_log = 2;
		else if (!ft_strcmp(args[i], "-complete"))
			g_smart = 0;
		else
			display_usage(USAGE_FILE);
		i++;
	}
}

int				main(int argc, char **args)
{
	set_params(argc, args);
	lemin();
	system("leaks lem-in"); // DEL
}
