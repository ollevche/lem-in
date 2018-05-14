
#include "lemin.h"

int		read_ants()
{
}

void	read_rooms_and_links()
{
}

void	print_input(int ants, t_room *room, t_link *link) // TODO: test it
{
	ft_printf("%d\n", ants);
	while (room)
	{
		if (room->comment)
			ft_printf("#%s", room->comment);
		if (room->command)
			ft_printf("##%s", room->command);
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
	}
	while (link)
	{
		if (link->comment)
			ft_printf("#%s", link->comment);
		ft_printf("%s-%s", link->from, link->to);
		link = link->next;
	}
	ft_printf("\n");
}