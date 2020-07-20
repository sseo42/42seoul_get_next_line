/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 21:18:22 by sseo              #+#    #+#             */
/*   Updated: 2020/04/09 23:15:24 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

/*
** get_next_line.c
*/
int						where_is(char *s, int c);
char					*ft_my_strjoin(char **s1, char *s2);
int						ft_read(int fd, char ***s);
int						ft_binary_split(char **line, char **storage, char sep);
int						get_next_line(int fd, char **line);

/*
** get_next_line_utils.c
*/
char					*ft_parsing(char *src, int start, int end);
int						ft_array_size(char **a);
size_t					ft_free_all(char ***s, int to_where);
char					**ft_new_2d_array(char ***s, int new_size, int size);
int						ft_update(int fd, char ***s);

#endif
