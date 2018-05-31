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

# define ERROR_CODE -1
# define FILEDES STDIN_FILENO

# include "libftprintf.h"

typedef struct	s_strlist
{
	char				*string;
	struct s_strlist	*next;
}				t_strlist;

typedef struct	s_room
{
	int				id;
	char			*name;
	int				x;
	int				y;
	t_strlist		*comment;
	t_strlist		*command;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	int				from;
	int				to;
	t_strlist		*comment;
	struct s_link	*next;
}				t_link;

/*
**	reading.c
*/

int					read_ants(void);
t_room				*read_rooms(void);
t_link				*read_links(void);

#endif
