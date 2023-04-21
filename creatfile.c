/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqaos <mqaos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 03:04:10 by mqaos             #+#    #+#             */
/*   Updated: 2023/04/21 02:46:11 by mqaos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

size_t	ft_strlenn(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		u;
	char	*s3;

	i = -1;
	u = -1;
	s3 = malloc(ft_strlenn(s1) + ft_strlenn(s2) + 1);
	if (!s3)
		return (0);
	while (s1 && s1[++i])
		s3[++u] = s1[i];
	i = -1;
	while (s2[++i] && s2)
	{
		s3[++u] = s2[i];
		if (s3[u] == '\n')
			break ;
	}
	s3[++u] = '\0';
	free(s1);
	return (s3);
}

int	removeline(char *str)
{
	int	start;
	int	sar;
	int	x;

	start = 0;
	sar = 0;
	x = 0;
	while (str[start])
	{
		if (x)
			str[sar++] = str[start];
		if (str[start] == '\n')
			x = 1;
		str[start] = '\0';
		start++;
	}
	return (x);
}

char	*get_next_line(int fd)
{
	static char	buffmax[2147483647];
	char		*buff;

	buff = NULL;
	while (buffmax[0] || read(fd, buffmax, 3) > 0)
	{
		buff = ft_join(buff, buffmax);
		if (removeline(buffmax))
			break ;
		if (read(fd, buffmax, 0) < 0)
			return (free(buff), NULL);
	}
	return (buff);
}

int	get_content(char *name)
{
   int fd;
   char *buf = NULL;
   char *result = ft_strdup("");
   while ((buf = get_next_line(0)))
        result = ft_strjoinn(result,buf);
   int len = strlen(result);
   fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
   if(fd == -1) {
      printf("Error creating file.\n");
      return (1);
   }
   if(write(fd, result, len) != len) {
      printf("Error writing to file.\n");
      close(fd);
      return 1;
   }
	return (fd);
}

int	creat_fd(char type, char *name)
{
	int fd;

	if (type == 'a')
	{
		fd = open(name, O_RDWR);
		if (fd == -1 && errno == ENOENT)
			fd = open(name, O_CREAT | O_RDWR, 0644);		
	}
	else if (type == 'h')
	{
		fd = open()
	}
	
}

void creat_files(t_cmd *cmd, t_exe *exe)
{
	
}