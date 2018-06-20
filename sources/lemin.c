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
**	TODO (maybe):
**	'-quick' combines sets without traversing;
*/

int g_log = 0;
int g_smart = 1;
int	g_maxset = INT_MAX;

static int		input_stage(int *ants, t_room **rooms,
								t_link **links, t_path **paths)
{
	t_strlist	*ants_comments;

	ants_comments = NULL;
	*rooms = NULL;
	*links = NULL;
	*paths = NULL;
	*ants = read_ants(&ants_comments);
	if (*ants < 0 ||
		read_graph(rooms, links) == ERROR_CODE ||
		!(*paths = get_paths(*rooms, *links)))
	{
		free_strlist(&ants_comments);
		return (ERROR_CODE);
	}
	display_input(ants_comments, *ants, *rooms, *links);
	free_strlist(&ants_comments);
	return (SUCCESS_CODE);
}

static int		output_stage(t_path *paths, t_room *rooms, int ants)
{
	t_set	*set;
	int		ret_code;

	display_paths("all of paths:\n", paths, rooms);
	set = get_set(paths, ants, rooms->id + 1);
	if (!set)
		return (ERROR_CODE);
	display_set("best ", set);
	ret_code = display_output(set, rooms, ants);
	free_set(&set);
	return (ret_code);
}

static void		lemin(void)
{
	int		ants;
	t_room	*rooms;
	t_link	*links;
	t_path	*paths;

	if (input_stage(&ants, &rooms, &links, &paths) == ERROR_CODE)
		terminate(&rooms, &links, &paths);
	if (output_stage(paths, rooms, ants) == ERROR_CODE)
		terminate(&rooms, &links, &paths);
	total_free(&rooms, &links, &paths);
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
		else if (!ft_strcmp(args[i], "-maxset"))
			g_maxset = (++i < argc) ? ft_atoi(args[i]) : 0;
		else
			display_usage(USAGE_FILE);
		if (!g_maxset)
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
