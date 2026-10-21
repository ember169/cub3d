#include "cub3d.h"

/* Verifie que le fichier termine en .cub */
int	check_extension(char *path, char *ext)
{
	char	*base;
	size_t	len;
	size_t	ext_len;

	base = ft_strrchr(path, '/');
	if (base)
		base++;
	else
		base = path;
	len = ft_strlen(base);
	ext_len = ft_strlen(ext);
	if (len <= ext_len)
		return (0);
	return (ft_strncmp(base + len - ext_len, ext, ext_len) == 0);
}
/* Verifie que l'argument est un fichier lisible */
int	check_readable_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY | O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (2);
	close(fd);
	return (0);
}

