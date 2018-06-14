/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:19:10 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:19:10 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_matrix(int ***matrix)
{
	int	i;

	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	total_free(t_room **rooms, t_link **links,
						t_strlist **ants_cmnts, t_set **set)
{
	free_rooms(rooms);
	free_links(links);
	free_strlist(ants_cmnts);
	free_set(set);
}
