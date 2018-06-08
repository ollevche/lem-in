/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ollevche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 14:54:12 by ollevche          #+#    #+#             */
/*   Updated: 2018/06/07 14:54:13 by ollevche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h" // TODO: 2d array with ids and lengths 

static int	max_len(int *paths_ids, int size, t_path *paths)
{
	int max_len;
	int	cur_len;
	int	i;

	max_len = 0;
	i = 0;
	while (i < size)
	{
		cur_len = get_path_by_id(paths, paths_ids[i])->length;
		if (cur_len > max_len)
			max_len = cur_len;
		i++;
	}
	return (max_len);
}

static int	efficiency_of(int *set_paths, int size, int ants, t_path *all_paths)
{
	int	merge_value;
	int	merge_sum;
	int	in_total;
	int i;

	// ft_printf("PATHS IDS:\t"); // DEL
	// while (j < size)
	// {
	// 	ft_printf("%d\t", set_paths[j]);
	// 	j++;
	// } ft_printf("\n");

	merge_value = max_len(set_paths, size, all_paths) - 1;
	merge_sum = 0;
	i = 0;
	while (i < size)
	{
		merge_sum += merge_value - 
		(get_path_by_id(all_paths, set_paths[i])->length - 1) + 1;
		i++;
	}
	in_total = merge_value + ft_ceildiv(ants - merge_sum, size);
	return (in_total);
}

static int	set_order(int *arr, int size, int max_p)
{
	int i;
	int	mid;

	if (arr[0] > max_p - size)
		return (false);
	i = 1;
	while (i < size && arr[i] < max_p - i)
		i++;
	if (i < size)
		mid = ++arr[i - 1];
	while (i < size)
		arr[i++] = ++mid;
	return (true);
}

static int	len_of_paths(int *paths_ids, int size, t_path *paths)
{
	int	i;
	int	total_len;

	i = 0;
	total_len = 0;
	while (i < size)
	{
		total_len += get_path_by_id(paths, paths_ids[i])->length;
		i++;
	}
	return (total_len);
}

static int	*pick_some(t_path *paths, int amount) // TODO: intersection!
{
	int	*cur;
	int	*shortest;
	int	cur_len;
	int	shortest_len;
	int	max_p;
	int	i;

	cur = (int*)malloc(sizeof(int) * amount); // error
	max_p = paths->id;
	i = 0;
	while (i < amount)
	{
		cur[i] = i;
		i++;
	}
	shortest = NULL;
	shortest_len = INT_MAX;
	while (set_order(cur, amount, max_p))
	{
		i = amount - 1;
		while (cur[i] <= max_p)
		{
			cur_len = len_of_paths(cur, amount, paths);
			if (cur_len < shortest_len)
			{
				free(shortest);
				shortest = arr_n_copy(cur, amount); // error
				shortest_len = cur_len;
			}
			cur[i]++;
		}
	}
	free(cur);
	return (shortest);
}

static int	*prepare_paths(t_path *all_paths, int ants)
{
	int	amount;
	int	*cur;
	int	*next;
	int	cur_ef;
	int	next_ef;

	amount = 1;
	cur = NULL;
	next = NULL;
	cur_ef = INT_MAX;
	next_ef = cur_ef - 1;
	while (cur_ef >= next_ef)// && amount <= all_paths->id + 1)
	{
		free(cur);
		cur = next;
		cur_ef = next_ef;
		next = pick_some(all_paths, amount); // error
		next_ef = efficiency_of(next, amount, ants, all_paths);

		int j = 0; // DEL
		ft_printf("some set (paths ids):\t");
		while (j < amount)
		{
			ft_printf("%d\t", next[j]);
			j++;
		} ft_printf("\n");
		ft_printf("size = %d\n", j);
		ft_printf("efficiency = %d\n", next_ef);

		amount++;
	}
	free(next);

	// int j = 0; // DEL
	// ft_printf("best set (paths ids):\t");
	// while (j < amount - 2)
	// {
	// 	ft_printf("%d\t", cur[j]);
	// 	j++;
	// } ft_printf("\n");
	// ft_printf("size = %d\n", j);
	// ft_printf("efficiency = %d\n", cur_ef);

	return (cur);
}

t_path		*get_set(t_path *all_paths, int ants)
{
	int	*paths_ids;

	paths_ids = prepare_paths(all_paths, ants);
	if (!paths_ids)
		return (NULL);
	return (NULL); // redo
}
