/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:07:34 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/14 15:07:35 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		increment_after(int i, t_path **set_paths, int size)
{
	if (!set_paths[i]->prev)
		return (ERROR_CODE);
	set_paths[i] = set_paths[i]->prev;
	while (++i < size)
		if (set_paths[i - 1]->prev)
			set_paths[i] = set_paths[i - 1]->prev;
		else
			return (false);
	return (true);
}

int		**new_ants_map(t_set *set)
{
	int **a_map;
	int	p;
	int n;

	a_map = (int**)malloc(sizeof(int*) * (set->size + 1));
	if (!a_map)
		return (NULL);
	a_map[set->size] = NULL;
	p = -1;
	while (++p < set->size)
	{
		a_map[p] = (int*)malloc(sizeof(int) * (set->paths[p]->length + 1));
		if (!a_map)
		{
			free_tdarr(&a_map);
			return (NULL);
		}
		a_map[p][set->paths[p]->length] = -1;
		n = -1;
		while (++n < set->paths[p]->length)
			a_map[p][n] = 0;
	}
	return (a_map);
}

void	terminate(t_room **rooms, t_link **links, t_path **paths)
{
	if (errno)
		perror("Error");
	else
		ft_printf("ERROR\n");
	total_free(rooms, links, paths);
	system("leaks lem-in"); // DEL
	exit(EXIT_FAILURE);
}

int		operation_failure(t_strlist *comments, char *command)
{
	free_strlist(&comments);
	free(command);
	return (ERROR_CODE);
}
