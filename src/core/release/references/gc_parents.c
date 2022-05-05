/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_parents.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:31:44 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 12:59:48 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif
#include <stdlib.h>
#include "src/core/release/core.h"
#include "leaky.h"

static int	init_parents(int64_t ptr);
static int	grow_parents(int64_t ptr);
static int	has_parent(int64_t ptr, int64_t parent);

int	gc_add_parent(int64_t ptr, int64_t parent)
{
	size_t	i;

	if (has_parent(ptr, parent))
		return (LK_FAILURE);
	if (!gc_ptr(ptr)->parents && !init_parents(ptr))
		return (LK_FAILURE);
	if (gc_ptr(ptr)->parent_capacity == gc_ptr(ptr)->parent_count
		&& !grow_parents(ptr))
		return (LK_FAILURE);
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity && gc_ptr(ptr)->parents[i] != -1)
		i++;
	gc_ptr(ptr)->parents[i] = parent;
	gc_ptr(ptr)->parent_count++;
	return (LK_SUCCESS);
}

int	gc_remove_parent(int64_t ptr, int64_t parent)
{
	size_t	i;

	if (!gc_ptr(ptr)->parents || !has_parent(ptr, parent))
		return (LK_FAILURE);
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity
		&& gc_ptr(ptr)->parents[i] != parent)
		i++;
	if (i < gc_ptr(ptr)->parent_capacity)
	{
		gc_ptr(ptr)->parents[i] = -1;
		gc_ptr(ptr)->parent_count--;
	}
	return (LK_SUCCESS);
}

static int	init_parents(int64_t ptr)
{
	int64_t	*new;

	new = gc_icalloc(5, sizeof (int64_t));
	gc_ptr(ptr)->parents = new;
	if (!gc_ptr(ptr)->parents)
		return (gc_error(gc_error_allocation()));
	gc_memsetl(gc_ptr(ptr)->parents, -1, 5);
	gc_ptr(ptr)->parent_capacity = 5;
	return (LK_SUCCESS);
}

static int	grow_parents(int64_t ptr)
{
	int64_t	*new;
	size_t	new_parent_capacity;

	if (gc_ptr(ptr)->parent_capacity >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (gc_ptr(ptr)->parent_capacity > 100)
		new_parent_capacity = gc_ptr(ptr)->parent_capacity + 100;
	else
		new_parent_capacity = gc_ptr(ptr)->parent_capacity * 2;
	new = gc_icalloc(new_parent_capacity, sizeof (int64_t));
	if (!new)
		return (gc_error(gc_error_allocation()));
	gc_memsetl(new, -1, new_parent_capacity);
	gc_memmove(new, gc_ptr(ptr)->parents,
		gc_ptr(ptr)->parent_capacity * sizeof (int64_t));
	gc_ptr(ptr)->parent_capacity = new_parent_capacity;
	gc_free(gc_ptr(ptr)->parents);
	gc_ptr(ptr)->parents = new;
	return (LK_SUCCESS);
}

static int	has_parent(int64_t ptr, int64_t parent)
{
	size_t	i;

	if (!gc_is_valid_ptr_index(parent))
		return (LK_FALSE);
	if (!gc_ptr(ptr)->parents)
		return (LK_FALSE);
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity)
	{
		if (gc_ptr(ptr)->parents[i] == parent)
			return (LK_TRUE);
		i++;
	}
	return (LK_FALSE);
}
