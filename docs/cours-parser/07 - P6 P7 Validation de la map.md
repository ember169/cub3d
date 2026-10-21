---
tags: [cub3d, parsing, cours, P6, P7]
---

# 07 · P6 / P7 Validation de la map

← [Index](00%20-%20Index.md) · Fichiers : `map_check.c`, `rules.c`

## P6 · `check_chars` : caractères et joueur

On parcourt toute la grille :
- un caractère qui n'est pas dans `0 1 N S E W` ou espace → `E_MAPCHAR` ;
- on compte les `N S E W` ; s'il n'y en a pas exactement 1 → `E_PLAYER`.

La liste des caractères autorisés n'est **pas** dans `map_check.c` : elle vient de `is_map_char` dans `rules.c`.

> [!info] Points de variation (`rules.c`)
> ```c
> int	is_map_char(char c)  { return (c != '\0' && ft_strchr("01NSEW ", c) != NULL); }
> int	is_walkable(char c)  { return (c != '\0' && ft_strchr("0NSEW", c) != NULL); }
> ```
> Le bonus fournira `rules_bonus.c`, avec les mêmes prototypes plus `D` (porte) et `X` (sprite). `map_check.c` n'est **jamais modifié** : le Makefile choisit quel `rules` compiler.
>
> Pourquoi `c != '\0'` : `ft_strchr("01NSEW ", '\0')` renvoie un pointeur **non nul**, vers le terminateur de la chaîne. Sans ce test, `'\0'` serait un caractère valide.

## P7 · `check_map` : la map est-elle fermée ?

### La règle

> **Toute case marchable a ses 4 voisines (haut, bas, gauche, droite) dans la grille, et aucune n'est un espace.**

Le bord de la grille et l'espace sont traités **pareil** : c'est du vide.

```c
static int	is_void(t_map *map, int y, int x)
{
	return (y < 0 || x < 0 || y >= map->h || x >= map->w
		|| map->grid[y][x] == ' ');
}
```

> [!important] L'ordre dans `is_void` compte
> `||` est **paresseux** : si `y < 0` est vrai, la suite n'est pas évaluée. On ne lit donc **jamais** `grid[-1][x]`. Si on mettait `grid[y][x] == ' '` en premier, ce serait une lecture hors limites.

### Pourquoi cette règle suffit (la preuve à savoir redire)

1. Le joueur ne passe d'une case à l'autre **que par un côté** (collisions par axe, module M).
2. Un rayon (DDA) avance aussi case par case, en changeant **une seule coordonnée à la fois**.
3. Donc, si **aucune case marchable ne partage un côté avec le vide**, aucun chemin (joueur ou rayon) ne peut atteindre le vide.

**Et les diagonales ?** Pour passer de `(x, y)` à `(x+1, y+1)`, il faudrait traverser `(x+1, y)` ou `(x, y+1)`. Si la diagonale est du vide et qu'on est fermé, ces deux cases sont forcément des murs (sinon elles seraient marchables et toucheraient le vide). Inutile de les tester.

### Exemples

```
i_irregular_open          i_hole_inside            v_inner_void (VALIDE)
1111··                    111111                   1111111
100001  ← (4,1) '0'       100001                   1000001
1N0001    a pour voisin   10 001  ← (2,2) espace   1011101
111111    haut (4,0) '·'  1N0001    voisin de '0'  101 101  ← espace entouré
          → E_OPENMAP     111111    → E_OPENMAP    1011101    de murs : aucun
                                                   100N001    '0' ne le touche
                                                   1111111    → OK
```

Le **joueur est marchable** (`N S E W` dans `is_walkable`) : `i_player_on_edge` (`11N111`) est donc rejeté.

## Pourquoi pas un flood fill (choix à défendre)

| | Règle des voisins (notre choix) | Flood fill récursif depuis le joueur |
|---|---|---|
| Pile | **aucune** récursion | profondeur = nombre de cases atteignables. `v_big_120x80` ≈ 9 000 appels imbriqués ; une map 1000 × 1000 dépasse la pile de 8 Mo → **segfault** |
| Mémoire | aucune | copie de la grille à « peindre », puis à libérer |
| Zones non atteignables | **vérifiées** aussi (plus strict) | ignorées : une île ouverte loin du joueur passe |
| Code | 2 boucles + `is_void` | récursion + copie + nettoyage |
| Complexité | O(w × h), 4 tests par case | O(w × h) aussi |

> [!note] Si un correcteur préfère le flood fill
> C'est une réponse acceptée aussi. Mais il faut alors le faire **itératif** (pile explicite), et assumer qu'il ne vérifie pas les zones non atteignables. `v_two_islands` montre notre choix : deux zones fermées séparées sont acceptées, parce que **chacune** est fermée.

## `err_row`, `err_col`

`check_map` renvoie aussi la position de la première case fautive. Elle ne sert pas au message (le sujet ne la demande pas), mais elle est très utile pour **déboguer** une map : `printf` à cet endroit, et tu sais exactement où est le trou.

→ Suite : [08 - P8 Joueur](08%20-%20P8%20Joueur.md)
