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
	(void)rooms; // free it
	(void)links; // free it
	if (errno)
		perror("Error");
	else
		ft_printf("ERROR\n");
	exit(EXIT_FAILURE);
}

static void	print_comments(t_strlist *comments)
{
	if (!comments)
		return ;
	while (comments->next)
		comments = comments->next;
	while (comments)
	{
		ft_printf("%s\n", comments->str);
		comments = comments->prev;
	}
}

static void	display_input(int ants, t_room *rooms, t_link *links)
{
	t_room	*iterator;

	iterator = rooms;
	ft_printf("%d\n", ants);
	while (iterator->next)
		iterator = iterator->next;
	while (iterator)
	{
		print_comments(iterator->comments);
		if (iterator->command)
			ft_printf("%s\n", iterator->command);
		ft_printf("%s %d %d\n",
			iterator->name, iterator->x, iterator->y);
		iterator = iterator->prev;
	}
	while (links->next)
		links = links->next;
	while (links)
	{
		print_comments(links->comments);
		ft_printf("%s-%s\n", get_room(rooms, links->from)->name,
			get_room(rooms, links->to)->name);
		links = links->prev;
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
	// TODO: an algorithm
	// system("leaks lem-in");
	// global free
	return (0);
}
