/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 18:44:24 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/04 18:44:25 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	*arr_n_copy(int *arr, int size)
{
	int	*copy;
	int	i;

	copy = (int*)malloc(sizeof(int) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = arr[i];
		i++;
	}
	copy[i] = -1;
	return (copy);
}

int	arr_get_last_elem(int *arr)
{
	int i;
	int	el;

	i = 0;
	while (arr[i] != -1)
		i++;
	if (i > 0)
		el = arr[i - 1];
	else
		el = -1;
	return (el);
}

int	*to_arr(int elem)
{
	int	*arr;

	arr = (int*)malloc(sizeof(int) * 2);
	if (!arr)
		return (NULL);
	arr[0] = elem;
	arr[1] = -1;
	return (arr);
}

int	*arr_extend(int *arr, int elem)
{
	int	i;
	int	*copy;

	i = 0;
	while (arr[i] != -1)
		i++;
	copy = (int*)malloc(sizeof(int) * (i + 2));
	if (!copy)
		return (NULL);
	i = 0;
	while (arr[i] != -1)
	{
		copy[i] = arr[i];
		i++;
	}
	copy[i] = elem;
	copy[i + 1] = -1;
	return (copy);
}

int	arr_contains(int *nodes, int target)
{
	while (*nodes != -1 && *nodes != target)
		nodes++;
	return (*nodes == target);
}
