	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   get_next_line.c                                    :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: tjkruger <tjkruger@student.42.fr>          +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2024/11/13 14:06:32 by tjkruger          #+#    #+#             */
	/*   Updated: 2024/12/09 17:53:42 by tjkruger         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "../include/get_next_line.h"

	char	*ft_strchr(const char *s, int c)
	{
		if (!s)
			return (NULL);
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
		}
		if (c == '\0')
			return ((char *)s);
		else
			return (NULL);
	}

	char	*ft_strcpy(char *dest, const char *src)
	{
		int	i;

		i = 0;
		while (src && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}

	// #include <stdio.h>
	char	*ft_strjoin(char *s1, char *s2)
	{
		char	*str;
		int		len1;
		int		len2;

		len1 = 0;
		len2 = 0;
		if ((!s1 || !*s1) && (!s2 || !*s2))
			return (NULL);
		if (s1)
			len1 = ft_strlen(s1);
		if (s2)
			len2 = ft_strlen(s2);
		str = malloc(len1 + len2 + 1);
		if (!str)
			return (free(s1), NULL);
		ft_strcpy(str, s1);
		ft_strcpy(str + len1, s2);
		if (!str)
			return (free(s1), NULL);
		str[len1 + len2] = '\0';
		free(s1);
		return (str);
	}

	char	*read_until_nl(char *line, int bytes_read, int fd, char *buffers)
	{
		while (!ft_strchr(line, '\n') && bytes_read > 0)
		{
			bytes_read = read(fd, buffers, BUFFER_SIZE);
			if (bytes_read > 0)
				buffers[bytes_read] = '\0';
			else
				buffers[0] = '\0';
			if (bytes_read <= 0)
			{
				if (bytes_read < 0)
				{
					buffers[0] = '\0';
					return (free(line), NULL);
				}
				if (ft_strlen(line))
					return (line);
				return (free(line), NULL);
			}
			line = ft_strjoin(line, buffers);
			if (!line)
				return (NULL);
		}
		ft_strcpy(buffers, ft_strchr(line, '\n') + 1);
		*(ft_strchr(line, '\n') + 1) = 0;
		line = ft_strdup(line);
		return (line);
	}

	char	*get_next_line(int fd)
	{
		static char	buffers[BUFFER_SIZE + 1];
		char		*line;
		ssize_t		bytes_read;

		line = NULL;
		if (fd < 0)
			return (NULL);
		bytes_read = read(fd, buffers, 0);
		if (bytes_read < 0)
			return (buffers[0] = 0, NULL);
		line = ft_strjoin(line, buffers);
		bytes_read = 42;
		return (read_until_nl(line, bytes_read, fd, buffers));
	}

	// #include <fcntl.h>

	// int	main(void)
	// {
	// 	char	*tmp;

	// 	int fd = open("test.txt",
	// 					O_RDONLY); // Open the file for reading
	// 	while ((tmp = get_next_line(fd)) != NULL)
	// 	{
	// 		printf("%s\n", tmp); // Print the line
	// 		free(tmp);
	// 	}
	// 	close(fd);
	// 	return (0);
	// }