---
tags: [cub3d, moteur, cours, R3, raycasting]
---

# 07 · R3 Distance et hauteur

← [Index](00%20-%20Index.md) · Fichiers : `raycast.c`, `column.c`

## La distance : retirer le delta de trop

```c
/* La boucle du DDA a ajoute un delta de trop : on le retire.
** C'est la profondeur le long de dir (pas d'hypotenuse) : pas de fisheye */
static void	set_perp(t_ray *r)
{
	if (r->hit_side == 0)
		r->perp = r->side.x - r->delta.x;
	else
		r->perp = r->side.y - r->delta.y;
	if (r->perp < MIN_PERP)
		r->perp = MIN_PERP;
}
```

Au dernier tour du DDA, on a franchi la ligne **puis** ajouté `delta` pour préparer le franchissement suivant. `side − delta` revient donc au `t` du franchissement qui a touché le mur.

## Pourquoi ce `t` n'a pas d'effet fisheye

```
            mur droit
   ─────────────────────────────
     \          │          /
      \  perp   │ perp    /  perp     ← même profondeur partout
       \        │        /
        \  euclid. plus grande sur les bords
         \      │      /
          \     │     /
               pos
```

- **Distance euclidienne** (longueur du rayon) : plus grande sur les bords de l'écran. Un mur droit en face paraîtrait **bombé**, comme à travers un objectif fisheye.
- **Profondeur perpendiculaire** : la distance mesurée **le long de `dir`**, comme le fait une vraie caméra. Un mur droit reste droit.

Le rayon vaut `dir + plane × camera_x`. Comme `plane ⊥ dir` et `|dir| = 1`, sa composante le long de `dir` vaut **exactement 1**. Donc le `t` du point touché **est** sa profondeur le long de `dir`. Pas de `cos`, pas de correction : c'est pour ça que le rayon n'est pas normalisé (voir [05](05%20-%20R1%20Rayons%20et%20camera.md)).

> [!warning] `MIN_PERP`
> Collé contre un mur, `perp` peut valoir 0 (ou presque). `WIN_H / 0` ferait planter ou donnerait une hauteur absurde. `MIN_PERP = 0.0001` garantit une division sûre. La hauteur vaut alors 7 200 000 pixels, qui tient dans un `int`, et elle est ramenée à l'écran ci-dessous.

## La hauteur de la colonne

```c
/* Un mur de hauteur 1 a distance 1 remplit l'ecran. perp >= MIN_PERP,
** donc pas de division par 0 ; start et end sont ramenes dans l'ecran */
static void	col_bounds(t_col *c, double perp)
{
	c->line_h = (int)(WIN_H / perp);
	c->start = WIN_H / 2 - c->line_h / 2;
	if (c->start < 0)
		c->start = 0;
	c->end = WIN_H / 2 + c->line_h / 2;
	if (c->end >= WIN_H)
		c->end = WIN_H - 1;
}
```

| Grandeur | Formule | Sens |
|---|---|---|
| `line_h` | `WIN_H / perp` | hauteur à l'écran : inversement proportionnelle à la distance (perspective) |
| `start` | `WIN_H/2 − line_h/2` | haut du mur, centré sur l'horizon |
| `end` | `WIN_H/2 + line_h/2` | bas du mur (inclus) |

- À distance 1, le mur fait toute la hauteur de l'écran. À distance 2, la moitié. À distance 4, le quart.
- Le mur est **centré** sur la ligne d'horizon (`WIN_H / 2`) : les yeux du joueur sont à mi-hauteur des murs.
- `start` et `end` sont ramenés dans `[0, WIN_H − 1]` : quand on est très près, le mur dépasse l'écran et on ne dessine que la partie visible.

> [!question] Pourquoi `WIN_H` et pas une autre constante ?
> C'est le choix « un mur à distance 1 remplit l'écran ». Avec `WIN_W = 960`, `WIN_H = 720` et `FOV_PLANE = 0.66`, les cases paraissent à peu près cubiques. Si on change le format de la fenêtre sans changer le FOV, les murs paraissent écrasés ou étirés (voir les modifications live dans [11](11%20-%20Soutenance.md)).

## À retenir en 3 lignes

1. `perp = side − delta` : le `t` du franchissement qui a touché le mur.
2. Ce `t` est la profondeur le long de `dir`, parce que le rayon n'est pas normalisé : pas de fisheye.
3. `line_h = WIN_H / perp`, centré sur l'horizon, clampé à l'écran ; `MIN_PERP` évite la division par 0.

→ Suite : [08 - R4 R5 Colonne et texture](08%20-%20R4%20R5%20Colonne%20et%20texture.md)
