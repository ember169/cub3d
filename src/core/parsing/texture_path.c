#include "cub3d.h"

/*
** P3 - Chemins de textures (validation seulement, pas de MLX ici)
**
** char *parse_texture(t_game *g, int el, char *rest)
**     tok = ft_split(rest, ' ')                   NULL -> E_MALLOC
**     si nombre de mots de tok != 1               -> free_tab(tok) ; E_TEXPATH
**     si !check_extension(tok[0], ".xpm")         -> free_tab(tok) ; E_TEXPATH
**     si check_readable_file(tok[0]) != 0         -> free_tab(tok) ; E_TEXPATH
**         (dossier, inexistant, illisible)
**     g->sc.tex_path[el] = ft_strdup(tok[0])      (COPIE, pas le pointeur de tok)
**     free_tab(tok)                               (toujours AVANT de renvoyer)
**     si la copie a echoue -> E_MALLOC
**     renvoyer NULL
**
** Le chargement reel (mlx_xpm_file_to_image) se fait en G3 : E_TEXLOAD.
*/
