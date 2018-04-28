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

# define ERROR_ID -1;

# include "libftprintf.h"
# include "fcntl.h"

typedef struct	s_room
{
	int				id;
	char			*name;
	int				x;
	int				y;
	char			is_empty;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	int				from;
	int				to;
	char			is_burned;
	struct s_link	*next;
}				t_link;

/*
**	main.c
*/

void			lemin(int fd);

/*
**	util.c
*/

void			free_room(t_room *room);
void			free_link(t_link *link);
void			terminate(t_room *rooms, t_link *links);

#endif
