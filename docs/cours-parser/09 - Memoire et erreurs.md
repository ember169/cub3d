---
tags: [cub3d, parsing, cours, memoire]
---

# 09 · Mémoire et erreurs

← [Index](00%20-%20Index.md) · Fichiers : `exit.c`, `free.c`, `main.c`

## Le principe : tout ce qui est alloué est rattaché à `g`

Il n'existe **aucune** allocation « orpheline » pendant le parsing. Tout ce qui survit au-delà d'une fonction est accroché à la structure `g`, et `exit_game(g, …)` sait tout libérer.

| Allocation | Rattachée à | Libérée par | Quand |
|---|---|---|---|
| lignes du fichier | `g->sc.lines` | `free_scene` → `free_tab` | fin de `parse_scene` (OK) ou `exit_game` (erreur) |
| chemins de textures | `g->sc.tex_path[el]` | `free_scene` | `exit_game` |
| grille | `g->map.grid` | `free_tab` dans `exit_game` | `exit_game` |
| `tok` (split du chemin) | **locale** | `free_tab(tok)` dans `parse_texture` | toujours, avant le `return` |

`tok` est la seule allocation temporaire : elle naît et meurt dans `parse_texture`, avec un seul point de sortie (voir [04](04%20-%20P3%20Textures.md)).

## Pourquoi `exit_game` peut tout libérer sans se poser de questions

1. **`ft_bzero(&g, sizeof(g))` dans `main`** : tous les pointeurs valent `NULL` au départ.
2. **`free(NULL)` ne fait rien** (garanti par la norme C), et `free_tab(NULL)` renvoie tout de suite.
3. Après chaque `free`, le pointeur est remis à `NULL`, ce qui rend un double free impossible.

Donc, peu importe **où** l'erreur se produit, `exit_game` libère ce qui existe et ignore le reste.

## Les cas délicats, un par un

| Situation | Pourquoi il n'y a pas de fuite |
|---|---|
| malloc raté au milieu de `read_lines` | on continue à lire jusqu'à `NULL` en jetant les lignes (stash gnl vidé), puis `free_tab(tab)` |
| malloc raté au milieu de la grille | grille rattachée à `g` **avant** d'être remplie, et `ft_calloc` → les cases non remplies valent `NULL` |
| `ft_strdup` raté dans P3 | `tok` libéré quand même (point de sortie unique) |
| erreur en P7 alors que tout est alloué | `exit_game` libère `lines`, `tex_path`, `grid` |
| parsing réussi | `lines` libéré tout de suite (le fichier brut ne sert plus), le reste vit jusqu'à la fermeture |

## Les file descriptors

Chaque `open` a son `close` **dans la même fonction** (`check_readable_file`, `read_lines`). Aucun fd ne survit à une fonction, ce qui donne `--track-fds=yes` propre.

## Vérifié

```
VG=1 bash tests/run_tests.sh
```

Avec `--leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --track-fds=yes` : **0 fuite (même *still reachable*), 0 fd** sur les 61 fichiers invalides du parsing et les 20 valides.

## Exercice : prouver le chemin `E_MALLOC`

Dans une **branche jetable**, remplace le `malloc` de la 3e ligne dans `fill_grid` :

```c
if (y == 2)
	g->map.grid[y] = NULL;
else
	g->map.grid[y] = malloc(w + 1);
```

Lance valgrind sur `v_subject_small.cub` et vérifie : message `memory allocation failed`, **0 fuite**. Prédis d'abord ce que `free_tab` va libérer.

→ Suite : [10 - Soutenance](10%20-%20Soutenance.md)
