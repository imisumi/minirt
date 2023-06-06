/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:51:02 by imisumi           #+#    #+#             */
/*   Updated: 2023/01/31 13:34:45 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// recreates str without the current \n NO
char	*trim_line(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if (!str)
		return (free(str), NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			temp = gnl_strdup(str + (i + 1));
			free(str);
			if (!temp)
				return (NULL);
			str = temp;
			return (str);
		}
		i++;
	}
	if (!str[i])
		return (free(str), NULL);
	return (NULL);
}

// return the current \n NO
char	*sub_line(char *str)
{
	char	*temp;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	temp = gnl_substr(str, 0, i + 1);
	return (temp);
}

// reads file
char	*read_fd(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		i;

	i = 1;
	buffer[0] = '\0';
	while (i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (free(str), NULL);
		buffer[i] = '\0';
		temp = gnl_strjoin(str, buffer);
		if (!temp)
			return (free(str), NULL);
		str = temp;
		if (str[0] == '\0')
			return (free(str), NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	if (!str[0])
		return (free(str), NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	str = read_fd(fd, str);
	if (!str)
		return (NULL);
	current_line = sub_line(str);
	if (!current_line)
		return (NULL);
	str = trim_line(str);
	return (current_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	printf("BUFFER = %i\n", BUFFER_SIZE);
// 	fd = open("giant_line.txt", O_RDONLY);
// 	while (i < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	system("leaks -q a.out");
// 	close(fd);
// 	return (0);
// }
