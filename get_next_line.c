/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaxima <rmaxima@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:19:24 by rmaxima           #+#    #+#             */
/*   Updated: 2019/10/04 14:50:25 by rmaxima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_str(char **str, char **line, int reader)
{
	int				i;
	char			*tmp;

	i = 0;
	tmp = 0;
	if (!reader && (!(*str) || !(*str)[0]))
		return (0);
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	*line = ft_strsub(*str, 0, i);
	if ((*str)[i] == '\n')
		tmp = ft_strdup(ft_strchr(*str, '\n') + 1);
	free(*str);
	*str = tmp;
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	int				reader;
	char			buff[BUFF_SIZE + 1];
	static char		*str[10240];
	char			*ptr;

	if (fd < 0 || !line)
		return (-1);
	while ((reader = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[reader] = '\0';
		if (!str[fd])
			str[fd] = ft_strnew(1);
		ptr = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = ptr;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (reader == -1)
		return (-1);
	return (get_str(&str[fd], line, reader));
}
