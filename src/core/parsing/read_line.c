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
	lit TOUT le fichier dans g->sc.lines
	(tableau de chaînes, sans '\n', lignes vides conservées)
*/
char	**read_lines(char *path, int *err)
{
	char	**tab;
	char	*line;
	size_t	len;
	int		fd;

	tab = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		*err = 1;
	line = NULL;
	while (fd >= 0)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*err || tab_push(&tab, line))
		{
			*err = 1;
			free(line);
		}
	}
	if (fd >= 0)
		close(fd);
	if (*err)
	{
		free_tab(tab);
		return (NULL);
	}
	return (tab);
}