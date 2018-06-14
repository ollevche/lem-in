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

void	terminate(t_room **rooms, t_link **links,
						t_strlist **ants_cmnts, int **best_set)
{
	if (errno)
		perror("Error");
	else
		ft_printf("ERROR\n");
	total_free(rooms, links, ants_cmnts, best_set);
	exit(EXIT_FAILURE);
}

int		operation_failure(t_strlist *comments, char *command)
{
	free_strlist(&comments);
	free(command);
	return (ERROR_CODE);
}
