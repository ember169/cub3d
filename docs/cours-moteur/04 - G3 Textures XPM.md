---
tags: [cub3d, moteur, cours, G3]
---

# 04 · G3 Textures XPM

← [Index](00%20-%20Index.md) · Fichiers : `gfx_init.c`, `pixel.c`

## Le chargement

```c
/* Chaque texture garde sa propre taille : ne pas supposer 64x64 */
static void	load_texture(t_game *g, int i)
{
	t_img	*t;

	t = &g->tex[i];
	t->ptr = mlx_xpm_file_to_image(g->mlx, g->sc.tex_path[i], &t->w, &t->h);
	if (!t->ptr)
		exit_game(g, 1, E_TEXLOAD);
	t->addr = mlx_get_data_addr(t->ptr, &t->bpp, &t->line_len, &t->endian);
}
```

- `g->tex[i]` est indexé par `t_elem` : `tex[EL_NO]`, `tex[EL_SO]`, `tex[EL_WE]`, `tex[EL_EA]`. Le même indice sert au parser (`tex_path[EL_NO]`) et au rendu.
- `w` et `h` sont **remplis par la MLX** : une texture 128 × 128 ou 64 × 32 marche sans changer le code, parce que tout le rendu utilise `tex->w` et `tex->h`.
- `t->ptr` est rattaché à `g` **avant** le test : si la 3e texture échoue, les 2 premières sont libérées par `destroy_gfx`.

## Qui vérifie quoi : parser ou MLX ?

| Cas | Rejeté par | Message |
|---|---|---|
| chemin absent, 2 chemins, pas `.xpm` | P3 (parser) | `E_TEXPATH` |
| fichier inexistant ou illisible | P3 (parser, `open`) | `E_TEXPATH` |
| fichier vide (`i_texture_empty_file`) | G3 (`mlx_xpm_file_to_image` → `NULL`) | `E_TEXLOAD` |
| XPM corrompu (`i_texture_corrupted`) | G3 | `E_TEXLOAD` |

> [!question] Pourquoi ne pas tout vérifier dans le parser ?
> Savoir si un XPM est **valide**, c'est le décoder. La MLX le fait déjà et renvoie `NULL` en cas d'échec. Le parser vérifie ce qu'il peut sans la MLX (le chemin, l'extension, la lecture), la MLX vérifie le contenu.

> [!note] `mlx_xpm_file_to_image` ne regarde pas l'extension
> Un XPM renommé en `.png` se charge. C'est pour ça que l'extension `.xpm` est vérifiée par le parser (P3), pas par la MLX.

## `get_texel` : lire un pixel de texture

```c
/* Clamp : tex_x peut valoir w quand wall_x arrondit a 1.0 */
int	get_texel(t_img *tex, int x, int y)
{
	if (x < 0) x = 0;
	if (x >= tex->w) x = tex->w - 1;
	if (y < 0) y = 0;
	if (y >= tex->h) y = tex->h - 1;
	src = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}
```

Même formule d'adresse que `put_pixel` (voir [02](02%20-%20G1%20Framebuffer%20et%20pixels.md)), mais en lecture.

| | `put_pixel` | `get_texel` |
|---|---|---|
| hors limites | **ignore** le pixel | **ramène** la coordonnée dans la texture (clamp) |
| pourquoi | un pixel hors écran n'a pas à être dessiné | on doit **toujours** renvoyer une couleur ; un arrondi de `tex_pos` ou de `wall_x` peut donner `h` ou `w`, il faut lire le dernier pixel au lieu de sortir de la mémoire |

## Les textures du projet

| Fichier | Contenu |
|---|---|
| `textures/wall_{n,s,e,w}.xpm` | briques 64 × 64 faites main (ImageMagick), avec un tuyau à **gauche** et une plaque en **haut à gauche** |
| `textures/test/*.xpm` | générées par `tests/gen_maps.sh`, dont `corrupt.xpm` et `empty.xpm` pour les cas d'erreur |

> [!tip] Pourquoi un détail asymétrique
> Une brique est symétrique : si une face était affichée à l'envers, on ne le verrait pas. Avec le tuyau à gauche, une face retournée se voit immédiatement (le tuyau passe à droite). C'est le test visuel de la formule de `tex_x` (voir [08](08%20-%20R4%20R5%20Colonne%20et%20texture.md)).

## À retenir en 3 lignes

1. Une texture = une `t_img`, avec sa propre taille ; rien n'est codé en dur à 64.
2. Le parser valide le chemin, la MLX valide le contenu (`E_TEXLOAD`).
3. `get_texel` clampe, `put_pixel` ignore : lire doit toujours réussir, écrire hors écran n'a pas de sens.

→ Suite : [05 - R1 Rayons et caméra](05%20-%20R1%20Rayons%20et%20camera.md)
