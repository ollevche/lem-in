/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:32:15 by ollevche          #+#    #+#             */
/*   Updated: 2018/04/25 18:32:15 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	error(char is_fatal)
{
	if (is_fatal)
		ft_printf("FATAL ERROR\n");
	else
		ft_printf("ERROR\n");
	return (ERROR_ID);
}