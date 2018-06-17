/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:38:19 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 16:38:19 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

void		display_input(t_strlist *ants_cmnts, int ants,
							t_room *rooms, t_link *links)
{
	t_room	*iterator;

	print_comments(ants_cmnts);
	ft_printf("%d\n", ants);
	iterator = rooms;
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
		ft_printf("%s-%s\n", get_room_by_id(rooms, links->from)->name,
			get_room_by_id(rooms, links->to)->name);
		links = links->prev;
	}
}

static int	make_moves(int **ants_map, t_set *set, t_room *rooms, int ants)
{
	int			p;
	int			n;
	static int	ant_id;
	int			moves;

	p = 0;
	moves = 0;
	while (p < set->size)
	{
		n = set->paths[p]->length - 2;
		while (n > -1)
		{
			if (ants_map[p][n] && !ants_map[p][n + 1])
			{
				if ((n + 1) != (set->paths[p]->length - 1))
					ants_map[p][n + 1] = ants_map[p][n];
				ft_printf("L%d-%s ", ants_map[p][n], get_room_by_id(rooms, set->paths[p]->nodes[n + 1])->name);
				ants_map[p][n] = 0;
				moves++;
			}
			if (n == 0 && ants_map[p][n] == 0 && ant_id <= ants)
			{
				ants_map[p][n] = ant_id;
				ant_id++;
			}
			else
				n--;
		}
		p++;
	}
	return (moves);
}

int			display_output(t_set *set, t_room *rooms, int ants)
{
	int	**ants_map;

	ft_printf("\n");
	ants_map = new_ants_map(set);
	if (!ants_map)
		return (ERROR_CODE);
	while (make_moves(ants_map, set, rooms, ants))
		ft_printf("\n");
	free_tdarr(&ants_map);
	return (SUCCESS_CODE);
}
