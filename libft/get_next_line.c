/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:27:01 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/06/20 20:23:43 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//keeps reading until function finds '\n' character
//adds previously read chars to pointer saved
static void	ft_read_it(int fd, char **str, char *buff, ssize_t bytes_read)
{
	char	*saved;

	saved = 0;
	while (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		if (!(str[fd]))
			str[fd] = ft_calloc(sizeof(char), BUFFER_SIZE);
		saved = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = saved;
		if (ft_strchr(buff, '\n'))
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
}

//break down of ft_get_line function
static void	*ft_do_line(char **str, int len)
{
	char	*line;
	char	*saved;

	if ((*str)[len] == '\n')
	{
		line = ft_substr(*str, 0, len + 1);
		saved = ft_strdup(*str + len + 1);
		free(*str);
		*str = saved;
		if (!**str)
		{
			free(*str);
			*str = NULL;
		}
	}
	else
	{
		line = ft_strdup(*str);
		free(*str);
		*str = 0;
	}
	return (line);
}

static void	*ft_get_line(char **str)
{
	char	*line;
	int		len;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len])
		len++;
	line = ft_do_line(str, len);
	return (line);
}

//checks fd and BUFFER_SIZE
//reads a first time and checks
//ft_read_it is a loop to read enough buffers to get line
//ft_get_line separates chars before '\n' from the rest read
char	*get_next_line(int fd)
{
	static char	*str[FILE_SIZE];
	char		*buff;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (buff);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buff);
		return (NULL);
	}
	ft_read_it(fd, str, buff, bytes_read);
	if (!bytes_read && (!str[fd] || !*str[fd]))
		return (NULL);
	line = ft_get_line(&(str[fd]));
	return (line);
}
