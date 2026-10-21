#include "cub3d.h"

/*
** P2 - Dispatch des elements (NO SO WE EA F C)
**
** found = masque de bits : bit n = element n vu (ordre de t_elem)
**   doublon : found & (1 << el)      tout present : found == ALL_ELEMS
*/

/* Longueur ET contenu : "NOX" et "NO./a.xpm" ne sont pas "NO" */
static int	elem_id(char *word, int len)
{
	if (len == 2 && !ft_strncmp(word, "NO", 2))
		return (EL_NO);
	if (len == 2 && !ft_strncmp(word, "SO", 2))
		return (EL_SO);
	if (len == 2 && !ft_strncmp(word, "WE", 2))
		return (EL_WE);
	if (len == 2 && !ft_strncmp(word, "EA", 2))
		return (EL_EA);
	if (len == 1 && word[0] == 'F')
		return (EL_F);
	if (len == 1 && word[0] == 'C')
		return (EL_C);
	return (-1);
}

/* Delegue la valeur : P3 pour une texture, P4 pour une couleur */
static char	*parse_value(t_game *g, int el, char *rest)
{
	int	color;

	if (el <= EL_EA)
		return (parse_texture(g, el, rest));
	if (parse_rgb(rest, &color))
		return (E_COLOR);
	if (el == EL_F)
		g->sc.floor = color;
	else
		g->sc.ceil = color;
	return (NULL);
}

char	*parse_element(t_game *g, char *line)
{
	int		i;
	int		len;
	int		el;
	char	*msg;

	if (ft_strchr(line, '\t') || ft_strchr(line, '\r'))
		return (E_BADSPACE);
	i = 0;
	while (line[i] == ' ')
		i++;
	len = 0;
	while (line[i + len] && line[i + len] != ' ')
		len++;
	el = elem_id(line + i, len);
	if (el < 0 && (line[i] == '0' || line[i] == '1'))
		return (E_MISSING);
	if (el < 0)
		return (E_IDENT);
	if (g->sc.found & (1 << el))
		return (E_DUP);
	msg = parse_value(g, el, line + i + len);
	if (msg)
		return (msg);
	g->sc.found |= 1 << el;
	return (NULL);
}
