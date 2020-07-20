/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 21:14:16 by sseo              #+#    #+#             */
/*   Updated: 2020/04/09 23:19:47 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	error info:
**	1	->	A line bas been read
**	0	->	EOF has been reached
**	-1	->	An error happened (ignore)
**	(ex: wrong fd, wrong Buffer_size, read failed)
**	-2	->	not enough heap memory. (free all buff)
*/

int					where_is(char *s, int c)
{
	int				idx;

	idx = 0;
	while (1)
	{
		if (s[idx] == c)
			return (idx);
		if (!s[idx])
			break ;
		idx++;
	}
	return (-1);
}

char				*ft_my_strjoin(char **s1, char *s2)
{
	char			*out;
	int				s1_len;
	int				s2_len;

	s1_len = 0;
	s2_len = 0;
	while ((*s1)[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	if ((out = (char *)malloc((s1_len + s2_len + 1) * sizeof(char))))
	{
		out[s1_len + s2_len] = 0;
		s1_len = -1;
		s2_len = -1;
		while ((*s1)[++s1_len])
			out[s1_len] = (*s1)[s1_len];
		while (s2[++s2_len])
			out[s1_len + s2_len] = s2[s2_len];
	}
	free(*s1);
	*s1 = 0;
	return (out);
}

int					ft_read(int fd, char ***s)
{
	char			*reader;
	int				len;
	int				lf_idx;

	lf_idx = -1;
	if (!(reader = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return ((int)ft_free_all(s, INT_MAX) - 2);
	while (lf_idx == -1 && (len = read(fd, reader, BUFFER_SIZE)) > 0)
	{
		if (len == -1)
			break ;
		reader[len] = 0;
		if (!((*s)[fd] = ft_my_strjoin(&((*s)[fd]), reader)))
		{
			(*s)[fd] = (char *)malloc(sizeof(char));
			free(reader);
			reader = 0;
			return ((int)ft_free_all(s, INT_MAX) - 2);
		}
		lf_idx = where_is(reader, '\n');
	}
	free(reader);
	reader = 0;
	return ((len > 0) ? 1 : len);
}

int					ft_binary_split(char **line, char **storage, char sep)
{
	int				sep_idx;
	char			*temp;

	sep_idx = where_is(*storage, sep);
	if (sep == '\n')
	{
		if (!(temp = ft_parsing(*storage, sep_idx + 1, INT_MAX)))
			return (1);
		if (!(*line = ft_parsing(*storage, 0, sep_idx)))
			return (2);
	}
	else
	{
		if (!(temp = (char *)malloc(sizeof(char))))
			return (1);
		if (!(*line = ft_parsing(*storage, 0, sep_idx)))
			return (2);
		*temp = 0;
	}
	free(*storage);
	*storage = temp;
	temp = 0;
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		**storage;
	int				eror_case;
	int				flag;

	flag = -1;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (ft_update(fd, &storage))
		return (-2);
	if ((eror_case = ft_read(fd, &storage)) < 0)
		return (eror_case);
	if (where_is(storage[fd], '\n') != -1 && (++eror_case))
	{
		if (ft_binary_split(line, &(storage[fd]), '\n'))
			return ((int)ft_free_all(&storage, INT_MAX) - 2);
	}
	else if (ft_binary_split(line, &(storage[fd]), 0))
		return ((int)ft_free_all(&storage, INT_MAX) - 2);
	while (storage[++flag])
		if (*(storage[flag]))
			break ;
	if (flag == ft_array_size(storage) && !eror_case)
		return ((int)ft_free_all(&storage, INT_MAX));
	return ((!(*(storage[fd])) && !eror_case) ? 0 : 1);
}
