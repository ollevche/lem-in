/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 17:29:15 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/07 17:29:17 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path  *get_path_by_id(t_path *paths, int id)
{
    while (paths && paths->id != id)
        paths = paths->next;
    return (paths);
}