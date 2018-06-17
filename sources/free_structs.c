/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 12:27:27 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/01 12:27:28 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_strlist(t_strlist **list)
{
	t_strlist	*trash;
	t_strlist	*iter;

	if (!list)
		return ;
	iter = *list;
	while (iter)
	{
		trash = iter;
		iter = iter->next;
		free(trash->str);
		free(trash);
	}
	*list = NULL;
}

void	free_rooms(t_room **rooms)
{
	t_room	*trash;
	t_room	*iter;

	if (!rooms)
		return ;
	iter = *rooms;
	while (iter)
	{
		trash = iter;
		iter = iter->next;
		free(trash->name);
		free_strlist(&(trash->comments));
		free(trash->command);
		free(trash);
	}
	*rooms = NULL;
}

void	free_links(t_link **links)
{
	t_link	*trash;
	t_link	*iter;

	if (!links)
		return ;
	iter = *links;
	while (iter)
	{
		trash = iter;
		iter = iter->next;
		free_strlist(&(trash->comments));
		free(trash);
	}
	*links = NULL;
}

void	free_paths(t_path **paths)
{
	t_path	*trash;
	t_path	*iter;

	if (!paths)
		return ;
	iter = *paths;
	while (iter)
	{
		trash = iter;
		iter = iter->next;
		free(trash->nodes);
		free(trash);
	}
	*paths = NULL;
}

void	free_set(t_set **set)
{
	if (!set || !*set)
		return ;
	free((*set)->paths);
	free(*set);
	*set = NULL;
}
