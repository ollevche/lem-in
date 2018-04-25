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

void	lemin(int fd)
{
	int		av_ants;
	t_room	*rooms;
	t_link	*links;
	int		making;

	av_ants = ft_atoi(safe_gnl(fd));
	rooms = read_rooms(fd); // TODO: write it
	links = read_links(fd); // TODO: write it
	if (!rooms || !links)
	{
		free_rooms(rooms); // make a func for this type of errors
		free_links(links); // it should free rooms and links, return ERROR_ID
		return (ERROR_ID);
	}
	making = 1;
	while (making)
	{
		making = make_turn(&av_ants, rooms, links); // TODO: write it
		if (making == ERROR_ID)
		{
			free_rooms(rooms); // make a func for this type of errors
			free_links(links); // it should free rooms and links, return ERROR_ID
			return (ERROR_ID);
		}
	}
}

int		main(int argc, char **args)
{
	int		fd;
	int		result;

	if (argc > 1)
		fd = open(args[1], O_RDONLY);
	else
		fd = STDIN_FILENO;
	if (fd < 0)
		return (error(1));
	result = lemin(fd);
	if (fd != STDIN_FILENO)
		close(fd);
	return (result);
}