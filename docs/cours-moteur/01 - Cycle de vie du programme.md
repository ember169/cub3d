---
tags: [cub3d, moteur, cours, I1, E1]
---

# 01 · Cycle de vie du programme

← [Index](00%20-%20Index.md) · Fichiers : `main.c`, `gfx_init.c`, `exit.c`

## `main` en entier

```c
int	main(int argc, char **argv)
{
	t_game	g;

	ft_bzero(&g, sizeof(g));
	if (argc != 2)
		exit_game(&g, 1, E_USAGE);
	parse_scene(&g, argv[1]);
	gfx_init(&g);
	setup_hooks(&g);
	g.last_time = now_seconds();
	mlx_loop(g.mlx);
	exit_game(&g, 0, NULL);
	return (0);
}
```

Six lignes utiles, chacune est une **phase**. Un correcteur qui lit `main` voit tout le programme.

| Ligne | Pourquoi elle est là, à cet endroit |
|---|---|
| `ft_bzero(&g, …)` | tous les pointeurs valent `NULL`, donc `exit_game` est appelable **avant** même `mlx_init` (voir [cours-parser/09](../cours-parser/09%20-%20Memoire%20et%20erreurs.md)) |
| `argc != 2` | on vérifie les arguments avant tout le reste : aucune allocation, rien à libérer |
| `parse_scene` | **avant** `mlx_init` : un `.cub` invalide ne demande pas de serveur X. Les tests d'erreur passent même sans `DISPLAY`. |
| `gfx_init` | a besoin des chemins de textures, donc après le parsing |
| `setup_hooks` | a besoin de `g->win`, donc après `gfx_init` |
| `g.last_time = now_seconds()` | **juste** avant la boucle. Plus tôt, le premier `dt` compterait le temps de chargement (voir [09](09%20-%20Boucle%20de%20jeu%20et%20mouvement.md)). |
| `mlx_loop` | ne rend jamais la main en pratique : on sort par `exit_game` depuis un hook |
| `exit_game(&g, 0, NULL)` | filet de sécurité si `mlx_loop` revenait un jour (par exemple avec `mlx_loop_end`) |

## Ordre d'initialisation dans `gfx_init`

```
mlx_init  →  4 × mlx_xpm_file_to_image  →  mlx_new_window  →  mlx_new_image (frame)
```

> [!question] Pourquoi charger les textures avant d'ouvrir la fenêtre ?
> Une texture corrompue (`i_texture_corrupted`) fait quitter le programme. Si la fenêtre était déjà ouverte, elle apparaîtrait puis disparaîtrait aussitôt. Dans cet ordre, l'utilisateur voit juste `Error` dans le terminal. Les textures n'ont besoin que de `g->mlx`, pas de la fenêtre.

Chaque appel MLX est **testé** : `NULL` → `exit_game(g, 1, E_MLX)` (ou `E_TEXLOAD`). Ce qui a déjà été créé est rattaché à `g`, donc libéré.

## Ordre de destruction dans `destroy_gfx`

C'est **l'inverse** de la création :

```
textures  →  frame  →  fenêtre  →  mlx_destroy_display  →  free(g->mlx)
```

| Étape | Pourquoi dans cet ordre |
|---|---|
| images (textures, frame) d'abord | `mlx_destroy_image` a besoin de la connexion X encore ouverte |
| fenêtre ensuite | même raison |
| `mlx_destroy_display` | ferme la connexion X |
| `free(g->mlx)` | `mlx_init` a fait un `malloc` de la structure ; `mlx_destroy_display` ne la libère **pas** |

Chaque pointeur est testé avant destruction et remis à `NULL` après. `destroy_gfx` marche donc après un `gfx_init` raté à n'importe quelle étape, et même si `mlx_init` n'a jamais été appelé (erreur de parsing).

## `exit_game` en entier, côté moteur

```c
	if (msg)
		/* "Error\n" + msg sur stderr */
	if (g->ext_free)
		g->ext_free(g);      /* crochet bonus : NULL en mandatory */
	free_scene(&g->sc);
	free_tab(g->map.grid);
	g->map.grid = NULL;
	destroy_gfx(g);
	exit(status);
```

- `status` vaut **0** pour ESC et la croix, **1** pour une erreur. `run_tests.sh` vérifie ce code.
- `ext_free` : le bonus y branchera la libération de ses données (sprites, portes…) sans toucher au code commun.

## Les points de variation (`mandatory/rules.c`)

Quatre fonctions ont **le même prototype** en mandatory et en bonus. Le Makefile compile l'une **ou** l'autre :

| Fonction | Mandatory | Ce que le bonus pourra changer |
|---|---|---|
| `is_map_char(c)` | `0 1 N S E W` et espace | ajouter `D` (porte), `2` (sprite)… |
| `is_walkable(c)` | `0 N S E W` | idem |
| `is_solid(g, x, y)` | hors grille, `1` ou espace → solide | porte fermée = solide |
| `select_texture(g, r)` | 4 faces (convention 7.8) | texture de porte |

> [!tip] Pourquoi ce découpage
> Le code commun (`core/`) ne contient **aucun** `#ifdef BONUS`. Le bonus remplace un fichier entier, et le code qu'on évalue en mandatory reste simple.

## À retenir en 3 lignes

1. Parsing avant MLX : une erreur de fichier ne touche jamais au serveur X.
2. Textures avant fenêtre ; destruction dans l'ordre inverse, `free(g->mlx)` en dernier.
3. Une seule sortie : `exit_game`, code 0 (normal) ou 1 (erreur).

→ Suite : [02 - G1 Framebuffer et pixels](02%20-%20G1%20Framebuffer%20et%20pixels.md)
