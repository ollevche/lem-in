
#include "lemin.h"

void	lemin()
{
	int		ants;
	t_room	*room;
	t_link	*link;

	ants = read_ants();
	read_rooms_and_links(&room, &link);
	if (ants == ERROR_ID || !room || !link)
		terminate(room, link);
	print_input(ants, room, link);

	//TODO: place an algorithm here

	free_room(room);
	free_link(link);
}