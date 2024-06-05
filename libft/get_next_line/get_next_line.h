/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:33:53 by david             #+#    #+#             */
/*   Updated: 2023/11/08 00:46:10 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>

char	*ft_strchr2(const char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(const char *str);
char	*get_next_line(int fd);
void	*ft_calloc2(size_t nmemb, size_t size);
void	ft_bzero2(void *s, size_t n);

#endif