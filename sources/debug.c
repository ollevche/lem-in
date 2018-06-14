/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 19:44:24 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 19:44:24 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	display_paths(t_path *paths)
{
	int i;

	if (!paths)
		return ;
	while (paths)
	{
		ft_printf("path\t[id = %d][length = %d]:", paths->id, paths->length);
		i = 0;
		while (i < paths->length)
		{
			ft_printf("\t%d", paths->nodes[i]);
			i++;
		}
		ft_printf("\n");
		paths = paths->next;
	}
}

void	display_set(t_set *set)
{
	int i;

	if (!set)
		return ;
	ft_printf("set\t[size = %d][length = %d]:", set->size, set->length);
	i = 0;
	while (i < set->size)
	{
		ft_printf("\t%d", set->paths[i]->id);
		i++;
	}
	ft_printf("\n");
}