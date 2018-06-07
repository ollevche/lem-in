/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
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
