/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:27:20 by ymehlil           #+#    #+#             */
/*   Updated: 2023/01/25 18:39:21 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*ft_strchr1(char *s, int c);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strdup1(char *s);
char	*ft_line(char *stash);
char	*ft_read(int fd, char *stash);
char	*ft_new_stash(char *stash);

void	*ft_memmove1(void *dst, void *src, size_t len);

size_t	ft_strlen1(char *s);
#endif
