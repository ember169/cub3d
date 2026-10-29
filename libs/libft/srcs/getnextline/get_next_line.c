/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:14:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/02/05 13:05:42 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*  FUNCTION: get_next_line                                                   */
/*                                                                            */
/*  Returns a line read from given file descriptor                            */
/*                                                                            */
/*  @param fd  	  The file descriptor to read from                            */
/*  @return       Read line (str) / NULL if nothing to read or error occured  */
/*                                                                            */
/*  Example:                                                                  */
/*     int *arr = ft_calloc(10, sizeof(int));                                 */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

/*
** ensure_capacity:
**     Garanti que stash a suffisamment d'octets alloués. Si non, realloc
**
**     @param stash   pointeur vers la zone memoire.
**     @param needed  De combien d'octets on a besoin.
**     @return 		  0 si rien n'est fait / 1 si realloc / -1 si erreur
*/
static int	ensure_capacity(t_stash *s, size_t needed)
{
	size_t	new_cap;
	char	*new_ptr;

	if (s->cap >= needed)
		return (0);
	new_cap = needed + 8;
	new_ptr = ft_realloc(s->buf, s->cap, new_cap);
	if (!new_ptr)
		return (-1);
	s->buf = new_ptr;
	s->cap = new_cap;
	return (1);
}

/*
** extract_line:
**     - return tous les caracteres jusqu'a \\n (inclu) dans une str.
**	   - retire l'ensemble de la str returned de la chaine d'origine.
**
**     @param	s	str (ici stash[fd])
**     @return		la ligne trouvee / l'ensemble de la chaine
*/
static char	*extract_line(t_stash *s)
{
	size_t	i;
	size_t	line_len;
	size_t	rest_len;
	char	*line;

	if (!s || !s->buf || !s->buf[0])
		return (NULL);
	i = 0;
	while (s->buf[i] && s->buf[i] != '\n')
		i++;
	line_len = i;
	if (s->buf[i] == '\n')
		line_len++;
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, s->buf, line_len);
	line[line_len] = '\0';
	rest_len = ft_strlen(s->buf + line_len);
	ft_memmove(s->buf, s->buf + line_len, rest_len + 1);
	s->len = rest_len;
	return (line);
}

/*
** init_stash_buffer:
**     Initialise s et buffer
**
**     @param s 	  la stash.
**     @return 		 buffer / NULL si erreur
*/
static char	*init_stash_buffers(t_stash *s)
{
	char	*buffer;

	if (!s->buf)
	{
		s->cap = BUFFER_SIZE + 1;
		s->buf = malloc(s->cap);
		if (!s->buf)
			return (NULL);
		s->len = 0;
		s->buf[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	return (buffer);
}

/*
** read_loop:
**     Contenu de la boucle de lecture de fichier pour remplir la stash
**
**     @param fd      file descriptor
**     @param buffer  buffer temporaire
**     @param s       stash[fd]
**     @return n <= 0 si EOF/erreur, 1 sinon
*/
static int	read_loop(int fd, char *buffer, t_stash *s)
{
	int	n;

	n = read(fd, buffer, BUFFER_SIZE);
	if (n <= 0)
		return (n);
	buffer[n] = '\0';
	if (ensure_capacity(s, s->len + n + 1) == -1)
		return (-1);
	ft_memcpy(s->buf + s->len, buffer, n);
	s->len += n;
	s->buf[s->len] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static t_stash	stash[FD_MAX];
	t_stash			*s;
	char			*buffer;
	char			*line;
	ssize_t			n;

	if (fd < 0 || fd >= FD_MAX)
		return (NULL);
	s = &stash[fd];
	buffer = init_stash_buffers(s);
	if (!buffer)
		return (free(s->buf), s->buf = NULL, NULL);
	n = 1;
	while (n > 0 && !ft_strchr(s->buf, '\n'))
		n = read_loop(fd, buffer, s);
	if (n < 0 || (n == 0 && s->len == 0))
		return (free(buffer), free(s->buf), s->buf = NULL, NULL);
	line = extract_line(s);
	if (!line)
		return (free(buffer), free(s->buf), s->buf = NULL, NULL);
	if (n == 0 && s->len == 0)
		return (free(buffer), free(s->buf), s->buf = NULL, line);
	return (free(buffer), line);
}

// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	char	*str;

// 	fd1 = open("test.txt", O_RDONLY);
// 	fd2 = open("tst", O_RDONLY);

// 	printf("fd1 = %d, fd2 = %d\n", fd1, fd2);
// 	printf("[FD1]\n");
// 	while ((str = get_next_line(fd1)))
// 	{
// 		debug_print(str);
// 		free(str);
// 	}

// 	printf("\n[FD2]\n");
// 	while ((str = get_next_line(fd2)))
// 	{
// 		debug_print(str);
// 		free(str);
// 	}
// 	return (1);
// }
