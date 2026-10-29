---
tags: [cub3d, moteur, cours, R2, raycasting]
---

# 06 · R2 DDA

← [Index](00%20-%20Index.md) · Fichier : `raycast.c`

## Le problème : trouver le premier mur touché

Avancer le rayon par petits pas fixes (`pos += ray × 0.01`) est lent et **rate des cases** : un rayon qui frôle le coin d'un mur peut passer « à travers » entre deux pas. Le DDA (*Digital Differential Analyzer*) avance **d'une ligne de grille à la suivante**. Il visite chaque case traversée, une seule fois, sans jamais en sauter.

## Le paramètre `t`

Un point du rayon s'écrit `pos + t × ray`. Toutes les grandeurs du DDA sont des **valeurs de `t`**, pas des distances en cases.

## `delta` : combien de `t` pour traverser une case

```c
if (r->dir.x == 0)
	r->delta.x = 1e30;
else
	r->delta.x = fabs(1 / r->dir.x);
```

- Pour avancer de **1** en x, il faut `t = 1 / |ray.x|`. C'est la même valeur pour chaque case : le rayon est droit.
- `ray.x == 0` (rayon parfaitement vertical) : il ne franchit **jamais** de ligne verticale. `1e30` veut dire « infiniment loin », sans diviser par zéro. La comparaison `side.x < side.y` sera toujours fausse, donc on n'avance qu'en y.

## `step` et `side` : sens et premier franchissement

```c
if (r->dir.x < 0)
{
	r->step_x = -1;
	r->side.x = (pos.x - r->map_x) * r->delta.x;
}
else
{
	r->step_x = 1;
	r->side.x = (r->map_x + 1.0 - pos.x) * r->delta.x;
}
```

```
        map_x        map_x+1
          │             │
          │   pos ●─────┼──► ray (x > 0)
          │       ◄────►│
          │  map_x+1−pos.x   → side.x = cette distance × delta.x
```

| Variable | Sens |
|---|---|
| `step_x` | +1 si le rayon va vers l'Est, −1 vers l'Ouest |
| `side.x` | `t` au **prochain** franchissement d'une ligne verticale |
| `side.y` | idem pour les lignes horizontales |

Au départ, le joueur est au milieu d'une case : la distance jusqu'à la première ligne est une **fraction** de case (`pos.x − map_x` ou `map_x + 1 − pos.x`), multipliée par `delta`.

## La boucle

```c
/* Le plus petit side = la prochaine ligne franchie ; on visite donc
** chaque case traversee, sans jamais sauter un coin de mur */
void	run_dda(t_game *g, t_ray *r)
{
	r->hit_side = 0;
	while (!is_solid(g, r->map_x, r->map_y))
	{
		if (r->side.x < r->side.y)
		{
			r->side.x += r->delta.x;
			r->map_x += r->step_x;
			r->hit_side = 0;
		}
		else
		{
			r->side.y += r->delta.y;
			r->map_y += r->step_y;
			r->hit_side = 1;
		}
	}
}
```

À chaque tour, on compare les deux prochains franchissements et on fait **le plus proche** :
- `side.x < side.y` → on franchit d'abord une ligne **verticale** : on passe à la case de gauche ou de droite, `hit_side = 0`.
- sinon → une ligne **horizontale** : case du dessus ou du dessous, `hit_side = 1`.

On s'arrête dès que la case est solide.

| `hit_side` | ligne franchie | face touchée |
|---|---|---|
| 0 | verticale (x constant) | face **Est ou Ouest** d'un mur |
| 1 | horizontale (y constant) | face **Nord ou Sud** d'un mur |

## Pourquoi la boucle finit toujours

```c
/* Hors grille et espace comptent comme des murs : le DDA s'arrete toujours */
int	is_solid(t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || x >= g->map.w || y >= g->map.h)
		return (1);
	return (g->map.grid[y][x] == '1' || g->map.grid[y][x] == ' ');
}
```

- La map est **fermée** (P7) : en pratique, le rayon touche un `1` avant de sortir.
- Même si ce n'était pas le cas, une case hors grille est solide : le rayon s'arrête au bord, sans lire hors du tableau.
- Les bornes sont testées **avant** l'accès à `grid[y][x]`. Dans l'autre ordre, on lirait hors limites.

## Exemple à la main

Joueur en `(2.5, 2.5)`, rayon `(1, 0.5)`.

| | x | y |
|---|---|---|
| `delta` | 1 / 1 = **1** | 1 / 0.5 = **2** |
| `step` | +1 | +1 |
| `side` initial | (3 − 2.5) × 1 = **0.5** | (3 − 2.5) × 2 = **1** |

| Tour | comparaison | action | `side` après | case |
|---|---|---|---|---|
| 1 | 0.5 < 1 | x | (1.5, 1) | (3, 2) |
| 2 | 1.5 ≥ 1 | y | (1.5, 3) | (3, 3) |
| 3 | 1.5 < 3 | x | (2.5, 3) | (4, 3) |

Vérification : à `t = 1`, le rayon est en `(3.5, 3)`, sur la ligne `y = 3`. C'est bien le 2e franchissement.

## À retenir en 3 lignes

1. `delta` = `t` pour traverser une case ; `side` = `t` jusqu'à la prochaine ligne.
2. On franchit toujours la ligne la plus proche : aucune case n'est sautée.
3. `hit_side` dit si on a touché une face Est/Ouest (0) ou Nord/Sud (1).

→ Suite : [07 - R3 Distance et hauteur](07%20-%20R3%20Distance%20et%20hauteur.md)
