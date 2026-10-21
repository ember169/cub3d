---
tags: [cub3d, parsing, cours, P5]
---

# 06 · P5 Construction de la grille

← [Index](00%20-%20Index.md) · Fichier : `map_build.c`

## Ce que fait `build_map(g, lines)`

`lines` pointe sur la ligne qui suit le 6e élément.

1. Sauter les lignes blanches. S'il ne reste rien → `E_NOMAP`.
2. `h` = nombre de lignes **non blanches consécutives** : c'est la map.
3. Tout ce qui suit doit être blanc. Sinon → `E_MAPGAP`.
4. `w` = longueur de la plus longue ligne.
5. Construire une grille `h × w` **complétée par des espaces**.

## L'idée clé : une grille rectangulaire

```
fichier            grille 5 × 3   (· = espace ajouté)
111111             111111
1N01               1N01··
111111             111111
```

> [!important] Pourquoi compléter avec des espaces
> 1. **Sécurité** : toutes les étapes suivantes (P6, P7, DDA, collisions, minimap) peuvent lire `grid[y][x]` pour **tout** `0 ≤ x < w` et `0 ≤ y < h`, sans vérifier la longueur de chaque ligne.
> 2. **Sens** : « au-delà de la fin de la ligne », c'est du **vide**, exactement comme un espace. Une ligne plus courte que ses voisines est donc traitée par **la même règle** que les espaces (voir [07](07%20-%20P6%20P7%20Validation%20de%20la%20map.md)). Pas de cas particulier.

## Comment les lignes vides sont jugées

L'astuce : **une ligne blanche termine la map**. Tout ce qui suit doit être blanc.

| Fichier | `h` | Après la map | Résultat |
|---|---|---|---|
| map, puis 3 lignes vides | 5 | blanc | ✅ `v_trailing_empty_lines` |
| `111`, ligne vide, `101`, … | 1 | `101` non blanc | `E_MAPGAP` (`i_empty_line_inside_map`) |
| map, ligne vide, `F 220,100,0` | 5 | `F…` non blanc | `E_MAPGAP` (`i_element_after_map`) |
| deux maps séparées | — | 2e map non blanche | `E_MAPGAP` (`i_two_maps`) |
| ligne `"   "` dans la map | — | blanche = coupure | `E_MAPGAP` (`i_spaces_line_inside_map`) |

Pas besoin de savoir *pourquoi* il y a du contenu après : « ligne vide dans la map » et « contenu après la map » sont **le même cas** vu par l'algorithme. D'où un seul message.

## La mémoire : rattacher **avant** de remplir

```c
g->map.grid = ft_calloc(h + 1, sizeof(char *));
if (!g->map.grid)
	return (E_MALLOC);
while (y < h)
{
	g->map.grid[y] = malloc(w + 1);
	if (!g->map.grid[y])
		return (E_MALLOC);       /* pas de free ici : c'est voulu */
	...
}
```

> [!question] Si le 3e `malloc` échoue, qui libère les 2 premières lignes ?
> `exit_game` → `free_tab(g->map.grid)`. Ça marche parce que :
> - la grille est **déjà** dans `g` ;
> - `ft_calloc` a mis **tous** les pointeurs à `NULL`. `free_tab` libère `grid[0]`, `grid[1]`, s'arrête sur `grid[2] == NULL`, puis libère le tableau.
>
> Aucune fonction de nettoyage locale n'est nécessaire, et c'est **une** ligne de code au lieu d'une boucle de libération partielle.

Le `h + 1` sert au `NULL` final : sans lui, `free_tab` continuerait dans la mémoire.

## Remplir une ligne

```c
ft_memset(g->map.grid[y], ' ', w);                          /* que des espaces */
ft_memcpy(g->map.grid[y], lines[y], ft_strlen(lines[y]));   /* la ligne au début */
g->map.grid[y][w] = '\0';
```

## Pièges évités

- Garder des lignes de longueurs différentes « pour économiser » : chaque `grid[y][x]` devient une lecture potentiellement hors limites.
- Confondre `h` (lignes, indice `y`) et `w` (colonnes, indice `x`). Convention : **`grid[y][x]`**, toujours ligne puis colonne.

→ Suite : [07 - P6 P7 Validation de la map](07%20-%20P6%20P7%20Validation%20de%20la%20map.md)
