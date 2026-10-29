/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 11:17:08 by lgervet           #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blank(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '\0');
}

static int	tab_push(char ***tab, char *line)
{
	char	**new;
	int		n;

	n = 0;
	while (*tab && (*tab)[n])
		n++;
	new = malloc((n + 2) * sizeof(char *));
	if (!new)
		return (1);
	ft_memcpy(new, *tab, n * sizeof(char *));
	new[n] = line;
	new[n + 1] = NULL;
	free(*tab);
	*tab = new;
	return (0);
}

/*
	Lit jusqu'a NULL meme apres une erreur : le stash statique de gnl est
	ainsi toujours vide en sortie (pas de "still reachable").
*/
static void	push_all_lines(int fd, char ***tab, int *err)
{
	char	*line;
	size_t	len;

	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*err || tab_push(tab, line))
		{
			*err = 1;
			free(line);
		}
		line = get_next_line(fd);
	}
}

/*
	lit TOUT le fichier dans g->sc.lines
	(tableau de chaînes, sans '\n', lignes vides conservées)
*/
char	**read_lines(char *path, int *err)
{
	char	**tab;
	int		fd;

	tab = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*err = 1;
		return (NULL);
	}
	push_all_lines(fd, &tab, err);
	close(fd);
	if (*err)
	{
		free_tab(tab);
		return (NULL);
	}
	return (tab);
}
