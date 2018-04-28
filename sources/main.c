/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:52:23 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/23 17:52:24 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//TODO: display "ERROR\n"

void	lemin(int fd)
{
	int		av_ants;
	t_room	*room;
	t_link	*link;

	av_ants = ft_atoi(safe_gnl(fd));
	room = read_rooms(fd); // TODO: write it
	link = read_links(fd); // TODO: write it
	if (!room || !link)
		terminate(room, link);
	//TODO: place an algorithm here
	free_room(room);
	free_link(room);
}

int		main(int argc, char **args)
{
	int		fd;

	if (argc > 1)
		fd = open(args[1], O_RDONLY);
	else
		fd = STDIN_FILENO;
	if (fd < 0)
		terminate(0, 0);
	lemin(fd);
	if (fd != STDIN_FILENO)
		close(fd);
	return (1);
}