---
tags: [cub3d, moteur, cours, R1, raycasting]
---

# 05 · R1 Rayons et caméra

← [Index](00%20-%20Index.md) · Fichiers : `raycast.c`, `frame.c`

## Le raycasting en une phrase

Pour **chaque colonne** de l'écran, on lance **un rayon** dans la grille 2D depuis le joueur. La distance au premier mur donne la **hauteur** du mur à dessiner dans cette colonne. 960 colonnes → 960 rayons par frame.

> [!question] C'est de la 3D ?
> Non, c'est de la « 2,5D ». Le monde est une grille 2D, tous les murs ont la même hauteur et sont verticaux, la caméra ne peut pas lever ou baisser la tête. C'est ce qui rend le calcul assez rapide pour un processeur de 1992.

## `render_frame` : la boucle sur les colonnes

```c
void	render_frame(t_game *g)
{
	x = 0;
	while (x < WIN_W)
	{
		cast_ray(g, x, &r);      /* R1–R3 : un rayon → une distance */
		draw_column(g, &r, x);   /* R4–R5 : une distance → des pixels */
		if (g->zbuf)
			g->zbuf[x] = r.perp; /* bonus sprites ; NULL en mandatory */
		x++;
	}
}
```

`render_frame` **dessine** dans `g->frame` mais n'affiche rien : c'est `game_loop` qui appelle `mlx_put_image_to_window`. En bonus, la minimap et les sprites pourront se dessiner entre les deux.

## La caméra : `pos`, `dir`, `plane`

```
                 plane (bord droit de l'écran)
          ◄───────────────●───────────────►
           \              │              /
            \             │ dir          /
             \            │ (longueur 1)/
              \           │            /
               \          │           /
                \         │          /
                 \        │         /
                  \       ●        /
                        pos
     camera_x = −1        0        +1
```

| Vecteur | Valeur | Sens |
|---|---|---|
| `pos` | position du joueur, en cases | centre de sa case au départ (P8) |
| `dir` | vecteur unitaire | là où il regarde |
| `plane` | `dir` tourné de +90°, × 0.66 | moitié droite de l'écran ; `−plane` est la moitié gauche |

Voir [cours-parser/08](../cours-parser/08%20-%20P8%20Joueur.md) pour le calcul initial.

## Un rayon par colonne

```c
camera_x = 2.0 * x / WIN_W - 1.0;
r->dir.x = g->pl.dir.x + g->pl.plane.x * camera_x;
r->dir.y = g->pl.dir.y + g->pl.plane.y * camera_x;
```

- `camera_x` va de **−1** (colonne 0, bord gauche) à presque **+1** (dernière colonne, bord droit).
- Le rayon = `dir` + une fraction de `plane`. Au centre de l'écran (`camera_x = 0`), le rayon est exactement `dir`.
- Le rayon **n'est pas normalisé**, et c'est voulu : c'est ce qui supprime l'effet fisheye plus tard (voir [07](07%20-%20R3%20Distance%20et%20hauteur.md)).

> [!warning] `2.0` et pas `2`
> `2 * x / WIN_W` en `int` vaut toujours 0 (division entière) : tous les rayons seraient `dir − plane`, l'écran entier afficherait la même colonne. Le `2.0` force le calcul en `double`.

## Le FOV

Le bord droit de l'écran est atteint par le rayon `dir + plane`. L'angle entre `dir` et ce rayon vaut `atan(|plane| / |dir|) = atan(0.66)`, soit environ 33°. Le champ de vision complet :

```
FOV = 2 × atan(FOV_PLANE) = 2 × atan(0.66) ≈ 66°
```

| `FOV_PLANE` | FOV |
|---|---|
| 0.58 | 60° |
| 0.66 | 66° (choix, proche de Wolfenstein) |
| 1.0 | 90° |

> [!question] Pourquoi `dir` + `plane` plutôt qu'un angle ?
> Avec un angle, chaque rayon demanderait un `cos` et un `sin` : 1 920 appels trigonométriques par frame. Avec des vecteurs, un rayon coûte deux multiplications et deux additions. La trigonométrie n'intervient qu'une fois par frame, pour **tourner** `dir` et `plane` (voir [09](09%20-%20Boucle%20de%20jeu%20et%20mouvement.md)).

## Le départ du rayon dans la grille

```c
r->map_x = (int)g->pl.pos.x;
r->map_y = (int)g->pl.pos.y;
```

La case où se trouve le joueur. `(int)` tronque vers 0, ce qui est correct ici parce que `pos` est toujours positive (le joueur est dans une map fermée).

## À retenir en 3 lignes

1. Un rayon par colonne : `ray = dir + plane × camera_x`, `camera_x` de −1 à +1.
2. FOV = `2 × atan(|plane|)` ; on règle le FOV avec `FOV_PLANE`, pas avec un angle.
3. Aucune trigonométrie par rayon.

→ Suite : [06 - R2 DDA](06%20-%20R2%20DDA.md)
