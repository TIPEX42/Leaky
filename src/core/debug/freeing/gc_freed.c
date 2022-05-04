/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_freed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/05/04 13:42:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

static void	free_childs(t_ptr *ptr);
static void	free_ptr(t_ptr *ptr);
static void	update_parents(t_ptr *ptr);

int	gc_free(void *ptr)
{
	t_gc	*allocator;
	t_ptr	*internal_ptr;

	allocator = gc_get();
	if (allocator->capacity == 0)
		return (LK_FAILURE);
	internal_ptr = gc_get_internal_ptr(ptr);
	if (!internal_ptr)
		return (LK_FAILURE);
	free_childs(internal_ptr);
	update_parents(internal_ptr);
	free_ptr(internal_ptr);
	return (LK_SUCCESS);
}

void	gct_free(void)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].temporary)
		{
			free_childs(&allocator->pointers[i]);
			update_parents(&allocator->pointers[i]);
			free_ptr(&allocator->pointers[i]);
		}
		i++;
	}
}

static void	free_childs(t_ptr *ptr)
{
	size_t	i;

	if (!ptr->childs)
		return ;
	i = 0;
	while (i < ptr->child_capacity)
	{
		if (ptr->childs[i])
			gc_free(ptr->childs[i]->address);
		i++;
	}
}

static void	update_parents(t_ptr *ptr)
{
	size_t	i;

	if (!ptr->parents)
		return ;
	i = 0;
	while (i < ptr->parent_capacity)
	{
		if (ptr->parents[i])
			gc_remove_child(ptr->parents[i], ptr);
		i++;
	}
}

static void	free_ptr(t_ptr *ptr)
{
	t_gc	*allocator;
	size_t	ptr_index;

	allocator = gc_get();
	ptr_index = gc_get_internal_ptr_index(ptr);
	if (ptr_index < allocator->first_free)
		allocator->first_free = ptr_index;
	allocator->ptrs_count--;
	free(ptr->address);
	if (ptr->childs)
		gc_free(ptr->childs);
	if (ptr->parents)
		gc_free(ptr->parents);
	*ptr = gc_null_ptr();
}