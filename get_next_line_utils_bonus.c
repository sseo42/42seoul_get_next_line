/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 21:23:21 by sseo              #+#    #+#             */
/*   Updated: 2020/04/09 23:17:02 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char			*ft_parsing(char *src, int start, int end)
{
	char		*out;
	int			idx;

	idx = 0;
	while (src[start + idx] && start + idx < end)
		idx++;
	if (!(out = (char *)malloc((idx + 1) * sizeof(char))))
		return (0);
	idx = 0;
	while (src[start + idx] && start + idx < end)
	{
		out[idx] = src[start + idx];
		idx++;
	}
	out[idx] = 0;
	return (out);
}

int				ft_array_size(char **a)
{
	int			idx;

	idx = 0;
	while (a[idx])
		idx++;
	return (idx);
}

size_t			ft_free_all(char ***s, int to_where)
{
	int			idx;

	idx = 0;
	while ((*s)[idx] && idx < to_where)
	{
		free((*s)[idx]);
		idx++;
	}
	free(*s);
	*s = 0;
	return (0);
}

char			**ft_new_2d_array(char ***s, int new_size, int size)
{
	char		**out;
	int			out_idx;

	out_idx = 0;
	if (!(out = (char **)malloc((new_size + 2) * sizeof(char *))))
		return ((char **)ft_free_all(s, INT_MAX));
	while (out_idx < size)
	{
		if (!(out[out_idx] = ft_parsing((*s)[out_idx], 0, INT_MAX)))
		{
			ft_free_all(&out, out_idx);
			return ((char **)ft_free_all(s, INT_MAX));
		}
		out_idx++;
	}
	ft_free_all(s, INT_MAX);
	while (out_idx <= new_size)
	{
		if (!(out[out_idx] = (char *)malloc(sizeof(char))))
			return ((char **)ft_free_all(&out, out_idx));
		*(out[out_idx]) = 0;
		out_idx++;
	}
	out[new_size + 1] = 0;
	return (out);
}

int				ft_update(int fd, char ***s)
{
	int			s_size;
	int			s_idx;

	s_idx = 0;
	if (!(*s))
	{
		if (!((*s) = (char **)malloc((fd + 2) * sizeof(char *))))
			return (-2);
		while (s_idx <= fd)
		{
			if (!((*s)[s_idx] = (char *)malloc(sizeof(char))))
			{
				ft_free_all(s, s_idx);
				return (-2);
			}
			*((*s)[s_idx]) = 0;
			s_idx++;
		}
		(*s)[fd + 1] = 0;
	}
	s_size = ft_array_size(*s);
	if (s_size <= fd)
		if (!(*s = ft_new_2d_array(s, fd, s_size)))
			return (-2);
	return (0);
}
