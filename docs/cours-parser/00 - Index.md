---
tags: [cub3d, parsing, cours]
---

# Cours : le parser de cub3D (module P)

> [!abstract] Objectif de ce cours
> À la fin, tu dois pouvoir **expliquer** chaque fonction du parser, **justifier** chaque choix devant un correcteur, et **retrouver** d'où vient n'importe quel message d'erreur sans regarder le code.

> [!tip] La suite
> Le reste du programme (MiniLibX, raycasting, boucle de jeu, build) est dans [cours-moteur](../cours-moteur/00%20-%20Index.md).

## Ordre de lecture

1. [01 - Vue d'ensemble](01%20-%20Vue%20d'ensemble.md) : le pipeline, la convention de retour, pourquoi un seul `exit`
2. [02 - P1 Lecture du fichier](02%20-%20P1%20Lecture%20du%20fichier.md) : pourquoi tout lire d'abord
3. [03 - P2 Elements et masque de bits](03%20-%20P2%20Elements%20et%20masque%20de%20bits.md) : `NO SO WE EA F C`, `found`
4. [04 - P3 Textures](04%20-%20P3%20Textures.md) : valider un chemin sans la MLX
5. [05 - P4 Couleurs (automate)](05%20-%20P4%20Couleurs%20(automate).md) : lire `220,100,0` sans `atoi` ni `split`
6. [06 - P5 Construction de la grille](06%20-%20P5%20Construction%20de%20la%20grille.md) : la grille rectangulaire
7. [07 - P6 P7 Validation de la map](07%20-%20P6%20P7%20Validation%20de%20la%20map.md) : la règle des 4 voisins, et pourquoi pas de flood fill
8. [08 - P8 Joueur](08%20-%20P8%20Joueur.md) : `pos`, `dir`, `plane`
9. [09 - Memoire et erreurs](09%20-%20Memoire%20et%20erreurs.md) : qui libère quoi, et pourquoi il n'y a jamais de fuite
10. [10 - Soutenance](10%20-%20Soutenance.md) : questions de correcteur, réponses courtes, exercices

## Carte des fichiers

| Unité | Fichier | Fonction publique | Peut renvoyer |
|---|---|---|---|
| P1 | `file.c`, `read_line.c` | `check_extension`, `check_readable_file`, `read_lines`, `is_blank` | `E_EXT`, `E_ISDIR`, `E_OPEN`, `E_MALLOC`, `E_EMPTY` |
| P2 | `elements.c` | `parse_element` | `E_BADSPACE`, `E_IDENT`, `E_MISSING`, `E_DUP` |
| P3 | `texture_path.c` | `parse_texture` | `E_TEXPATH`, `E_MALLOC` |
| P4 | `color.c` | `parse_rgb` | 1 → `E_COLOR` |
| P5 | `map_build.c` | `build_map` | `E_NOMAP`, `E_MAPGAP`, `E_MALLOC` |
| P6 | `map_check.c` | `check_chars` | `E_MAPCHAR`, `E_PLAYER` |
| P7 | `map_check.c` | `check_map` | 1 → `E_OPENMAP` |
| P8 | `player.c` | `init_player` | rien (ne peut pas échouer) |
| — | `rules.c` | `is_map_char`, `is_walkable` | points de variation mandatory/bonus |
| chef d'orchestre | `parse_scene.c` | `parse_scene` | **seul** à appeler `exit_game` |

## État vérifié (2026-10-21)

- Compilé avec `-Wall -Wextra -Werror` : 0 warning.
- `tests/run_tests.sh` avec valgrind : les **61** fichiers invalides qui relèvent du parsing donnent `Error` et le bon message, avec **0 fuite et 0 fd ouvert**.
- Les **20** maps valides passent le parsing, sans erreur valgrind.
- Restent « KO » **à juste titre** : `i_texture_corrupted` et `i_texture_empty_file`, rejetés plus tard en G3 (chargement MLX, `E_TEXLOAD`), et les maps valides tant qu'il n'y a pas de fenêtre (module G).
