---
tags: [cub3d, moteur, cours, makefile, tests]
---

# 10 · Build, tests et ressources

← [Index](00%20-%20Index.md) · Fichiers : `Makefile`, `tests/`, `textures/`

## Le Makefile

```make
CFLAGS  := -Wall -Wextra -Werror -g3 -std=gnu17
LDFLAGS := -L $(MLXPATH) -lmlx -L $(LIBPATH) -lft -lXext -lX11 -lm -lz

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
$(MLX):
	$(MAKE) -C $(MLXPATH) -f Makefile.mk INC=/usr/include CFLAGS="-O3 -std=gnu17 -I/usr/include"
$(LIBFT):
	$(MAKE) -C $(LIBPATH)
```

| Élément | Pourquoi |
|---|---|
| `SRCS` listés un par un | la Norme interdit les wildcards (`*.c`) dans le Makefile |
| `$(MLX)` et `$(LIBFT)` en dépendances | les deux bibliothèques sont construites automatiquement au premier `make` |
| pas de relink | si aucun `.o` n'a changé et que les `.a` existent, `make` ne refait rien |
| `-lXext -lX11` | la MiniLibX Linux repose sur X11 et l'extension MIT-SHM (images partagées) |
| `-lm` | `cos`, `sin`, `floor`, `fabs`, `sqrt` |

### Pourquoi `-std=gnu17`

Depuis GCC 15 (Fedora 42+, Nobara), le standard par défaut est **C23**. En C23, `int (*f)()` veut dire « fonction **sans** paramètre ». Or `mlx_hook` et `mlx_loop_hook` déclarent leur handler comme `int (*funct)()`. Passer `on_key_press(int, t_game *)` donne alors :

```
error: passing argument 4 of 'mlx_hook' from incompatible pointer type
```

`-std=gnu17` remet le standard par défaut de GCC 8 à 14, où `()` veut dire « paramètres non précisés ». Même code, même comportement sur toutes les machines. La MLX est compilée avec le même flag pour rester cohérente.

> [!warning] Points à vérifier avant la soutenance
> - **`-lz`** : la MiniLibX Linux actuelle n'a pas besoin de zlib (la roadmap dit que `-lmlx -lXext -lX11 -lm` suffit). Vérifier que ça compile sans, ou savoir dire pourquoi il est là.
> - **En-tête non suivi** : modifier `cub3d.h` ne recompile pas les `.c` (pas de `-MMD` / dépendances sur le header). Après une modification live dans `cub3d.h` (taille de fenêtre, FOV, vitesse), faire `make re`, sinon l'ancien binaire reste.
> - **Règle `bonus`** : commentée pour l'instant. Le sujet l'exige si on rend des bonus.
> - **`temp_move.c`** : à retirer de `SRCS` quand `core/move/` existe.

## Les tests

```bash
bash tests/gen_maps.sh          # génère maps/valid, maps/invalid, textures/test
make && bash tests/run_tests.sh
VG=1 bash tests/run_tests.sh    # + valgrind sur les cas d'erreur
```

| Ce que teste `run_tests.sh` | Comment |
|---|---|
| arguments (aucun, deux, fichier inexistant, vide) | doit sortir avec un code ≠ 0 et `Error` en 1re ligne de stderr |
| les 60 fichiers de `maps/invalid` | idem ; un `timeout` détecte une fenêtre ouverte par erreur, un code ≥ 128 un crash |
| les 20 fichiers de `maps/valid` | doivent **rester ouverts 2 s** (le `timeout` les tue : code 124 = OK). Ignorés sans `DISPLAY`. |
| avec `VG=1` | valgrind `--leak-check=full --show-leak-kinds=all --track-fds=yes` : 0 fuite, 0 fd |

> [!danger] `gen_maps.sh` efface `maps/`
> Le script fait `rm -rf maps "$T"` avant de régénérer. **`maps/demo/demo.cub` est supprimé** à chaque lancement (il n'est pas généré par le script). Il faut le restaurer avec `git checkout maps/demo`, ou déplacer la démo hors de `maps/`, ou ajouter sa génération au script.

> [!note] Fichier de suppression valgrind
> `run_tests.sh` utilise `tests/x11.supp` **s'il existe**. Il n'est pas dans le repo pour l'instant : sur certaines machines, la libX11 produit des faux positifs « still reachable » qui feraient échouer `VG=1`. À ajouter si ça arrive.

### Tests manuels (non scriptables)

| Test | Attendu |
|---|---|
| valgrind + quitter par ESC, puis par la croix | 0 fuite, 0 fd, code 0 |
| tenir W, Alt+Tab, revenir | le joueur s'est arrêté |
| minimiser, recouvrir, restaurer | image intacte |
| spawn N/S/E/W (`v_facing_*`) | texture de même nom en face, barre ou tuyau **à gauche** |
| coller chaque mur, chaque coin, en biais | glissement, jamais de traversée, pas de crash |
| `env -u DISPLAY ./cub3D maps/valid/v_min_3x3.cub` | `Error` + `minilibx initialisation failed`, 0 fuite |

### Les tests unitaires (`tests/unit/`)

`t_file.c`, `t_elements.c`, `t_parse.c` testent le parser fonction par fonction, sans fenêtre. C'est possible **parce que** les fonctions feuilles ne quittent jamais (voir [cours-parser/01](../cours-parser/01%20-%20Vue%20d'ensemble.md)). `debug_dump.c` affiche la scène parsée.

## Les ressources graphiques

| Fichier | Origine |
|---|---|
| `textures/wall_{n,s,e,w}.xpm` | faites main avec ImageMagick, 64 × 64, détail asymétrique (tuyau à gauche) pour repérer une face inversée |
| `textures/test/*` | générées par `gen_maps.sh` (dont `corrupt.xpm`, `empty.xpm`, `north.png`) |
| `textures/CREDITS.md` | licences : tout est création originale du binôme |
| `maps/demo/demo.cub` | 10 × 10 fermée, 4 piliers, spawn `N` face aux piliers |

## À retenir en 3 lignes

1. `-std=gnu17` : sans lui, GCC 15 refuse les handlers passés à `mlx_hook`.
2. `run_tests.sh` vérifie `Error` + code de sortie, et qu'une map valide garde la fenêtre ouverte.
3. Attention : `gen_maps.sh` efface `maps/demo` ; un changement dans `cub3d.h` demande `make re`.

→ Suite : [11 - Soutenance](11%20-%20Soutenance.md)
