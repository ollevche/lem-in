/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:01:25 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/23 18:01:25 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define ERROR_ID -1
# define FILEDES STDIN_FILENO

# include "libftprintf.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_room
{
	int				id;
	char			*name;
	int				x;
	int				y;
	char			*comment; // it can be at most one comment here, what about others?
	char			*command; // and here
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	int				from;
	int				to;
	char			*comment; // and here too
	struct s_link	*next;
}				t_link;

/*
**	lemin.c
*/

void			lemin();

/*
**	reading.c
*/

t_room			*read_rooms();
t_link			*read_links();
void			print_input(int ants, t_room *room, t_link *link);

/*
**	util.c
*/

void			free_rooms(t_room *room);
void			free_links(t_link *link);
void			terminate(t_room *rooms, t_link *links);

#endif
