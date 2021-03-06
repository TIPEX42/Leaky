/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:25:27 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 14:35:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

char	*gc_strdup(const char *s1)
{
	char	*newstr;

	if (!s1)
		return (NULL);
	newstr = gc_calloc(gc_strlen(s1) + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	gc_strlcpy(newstr, s1, gc_strlen(s1) + 1);
	return (newstr);
}

char	*gct_strdup(const char *s1)
{
	char	*newstr;

	if (!s1)
		return (NULL);
	newstr = gct_calloc(gc_strlen(s1) + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	gc_strlcpy(newstr, s1, gc_strlen(s1) + 1);
	return (newstr);
}
