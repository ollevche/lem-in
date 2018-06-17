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

void	display_traversing(t_path **set_paths, int size)
{
	int i;

	if (!set_paths || g_log < 2)
		return ;
	i = 0;
	ft_printf("[size = %d]\t", size);
	while (i < size)
	{
		ft_printf("%d ", set_paths[i]->id);
		i++;
	}
	ft_printf("\n");
}

void	display_invalid_traversing(t_path **set_paths, int size, int id)
{
	int i;

	if (!set_paths || g_log < 2)
		return ;
	i = 0;
	ft_printf("X[size = %d]\t", size);
	while (i < size)
	{
		if (i != id)
			ft_printf("%d ", set_paths[i]->id);
		else
			ft_printf("%dX ", set_paths[i]->id);
		i++;
	}
	ft_printf("\n");
}

void	display_paths(char *title, t_path *paths, t_room *rooms)
{
	int i;

	if (!paths || !rooms || !title || g_log < 1)
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

	if (!set || !title || g_log < 1)
		return ;
	ft_printf("%s", title);
	ft_printf("set\t[size = %d,\tlength = %d,\tefficiency = %d]\t",
				set->size, set->length, set->efficiency);
	i = 0;
	while (i < set->size)
	{
		ft_printf("%d (%d)", set->paths[i]->id, set->ants[i]);
		i++;
		if (i < set->size)
			ft_printf(" + ");
	}
	ft_printf("\n");
}
