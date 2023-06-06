/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:52:00 by imisumi           #+#    #+#             */
/*   Updated: 2023/01/31 13:05:52 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*gnl_strdup(char *s);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strchr(const char *s, int c);

#endif
