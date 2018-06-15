/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 19:44:24 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 19:44:24 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	display_paths(char *title, t_path *paths, t_room *rooms)
{
	int i;

	if (!paths || !rooms || !title || !g_log)
		return ;
	ft_printf("%s", title);
	while (paths->next)
		paths = paths->next;
	while (paths)
	{
		ft_printf("path_%d\t[length = %d]\t", paths->id, paths->length);
		i = 0;
		while (i < paths->length)
		{
			ft_printf("%s", get_room_by_id(rooms, paths->nodes[i])->name);
			i++;
			if (i < paths->length)
				ft_printf("-");
		}
		ft_printf("\n");
		paths = paths->prev;
	}
}

void	display_set(char *title, t_set *set)
{
	int i;

	if (!set || !title || !g_log)
		return ;
	ft_printf("%s", title);
	ft_printf("set\t[size = %d,\tlength = %d,\tefficiency = %d]\t",
				set->size, set->length, set->efficiency);
	i = 0;
	while (i < set->size)
	{
		ft_printf("%d", set->paths[i]->id);
		i++;
		if (i < set->size)
			ft_printf("+");
	}
	ft_printf("\n");
}
