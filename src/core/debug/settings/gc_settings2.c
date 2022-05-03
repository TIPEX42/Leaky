/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_settings2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:26:03 by njennes           #+#    #+#             */
/*   Updated: 2022/04/13 16:27:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/core.h"
#include "leaky.h"

int	can_change_settings(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->ptrs_count)
	{
		gc_add_error(gc_error_settings_after_allocation());
		return (LK_FALSE);
	}
	return (LK_TRUE);
}