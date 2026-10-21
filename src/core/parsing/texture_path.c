#include "cub3d.h"

/*
** P3 - Chemins de textures (validation seulement, pas de MLX ici)
** Le chargement reel (mlx_xpm_file_to_image) se fait en G3 : E_TEXLOAD.
**
** Un seul point de sortie : tok est libere sur TOUS les chemins.
** !tok[0] || tok[1] = "pas exactement un mot" (0 mot ou au moins 2).
*/
char	*parse_texture(t_game *g, int el, char *rest)
{
	char	**tok;
	char	*msg;

	tok = ft_split(rest, ' ');
	if (!tok)
		return (E_MALLOC);
	msg = NULL;
	if (!tok[0] || tok[1])
		msg = E_TEXPATH;
	else if (!check_extension(tok[0], ".xpm"))
		msg = E_TEXPATH;
	else if (check_readable_file(tok[0]) != 0)
		msg = E_TEXPATH;
	else
	{
		g->sc.tex_path[el] = ft_strdup(tok[0]);
		if (!g->sc.tex_path[el])
			msg = E_MALLOC;
	}
	free_tab(tok);
	return (msg);
}
