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
	while (links && links->next)
		links = links->next;
	while (links)
	{
		print_comments(links->comments);
		ft_printf("%s-%s\n", get_room_by_id(rooms, links->from)->name,
			get_room_by_id(rooms, links->to)->name);
		links = links->prev;
	}
}

static int	make_moves(int *ants_map_r, t_path *path, t_room *rooms, int ants)
{
	int			n;
	static int	ant_id = 1;
	int			moves;

	moves = 0;
	n = path->length - 2;
	while (n > -1)
	{
		if ((ants_map_r[n] || n == 0) && !ants_map_r[n + 1])
		{
			if (n != 0 || ant_id <= ants)
			{
				ants_map_r[n + 1] = (n == 0) ? ant_id++ : ants_map_r[n];
				moves += ft_printf("L%d-%s ", ants_map_r[n + 1],
							get_room_by_id(rooms, path->nodes[n + 1])->name);
				if (n + 1 == path->length - 1)
					ants_map_r[n + 1] = 0;
				ants_map_r[n] = 0;
				n = n ? n : n + 1;
			}
		}
		n--;
	}
	return (moves);
}

int			display_output(t_set *set, t_room *rooms, int ants)
{
	int	**ants_map;
	int	p;
	int moves;

	ft_printf("\n");
	ants_map = new_ants_map(set);
	if (!ants_map)
		return (ERROR_CODE);
	moves = 1;
	while (moves)
	{
		p = 0;
		moves = 0;
		while (p < set->size)
		{
			moves = make_moves(ants_map[p], set->paths[p], rooms, ants);
			p++;
		}
		ft_printf("\n");
	}
	free_tdarr(&ants_map);
	return (SUCCESS_CODE);
}
