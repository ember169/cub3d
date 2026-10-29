---
tags: [cub3d, moteur, cours, R4, R5, textures]
---

# 08 · R4 R5 Colonne et texture

← [Index](00%20-%20Index.md) · Fichiers : `column.c`, `rules.c`

## Quelle texture : `select_texture`

```c
/* Convention 7.8 : NO = texture vue en regardant vers le Nord (y < 0) */
t_img	*select_texture(t_game *g, t_ray *r)
{
	if (r->hit_side == 1)
	{
		if (r->dir.y < 0)
			return (&g->tex[EL_NO]);
		return (&g->tex[EL_SO]);
	}
	if (r->dir.x > 0)
		return (&g->tex[EL_EA]);
	return (&g->tex[EL_WE]);
}
```

| `hit_side` | signe du rayon | on regarde vers | texture |
|---|---|---|---|
| 1 | `ray.y < 0` | Nord | NO |
| 1 | `ray.y > 0` | Sud | SO |
| 0 | `ray.x > 0` | Est | EA |
| 0 | `ray.x < 0` | Ouest | WE |

**Convention choisie** : la texture `NO` est celle qu'on voit **en regardant vers le Nord**. Test immédiat : spawn `N` → le mur en face affiche `NO`.

> [!note] L'autre convention
> « NO = la face du mur **orientée** vers le Nord » existe aussi (c'est l'inverse : on la voit en regardant vers le Sud). Le sujet ne tranche pas. Si un correcteur l'attend, on échange NO↔SO et EA↔WE dans `select_texture` : 4 lignes.

## Où le rayon touche le mur : `wall_x`

```c
if (r->hit_side == 0)
	wall_x = g->pl.pos.y + r->perp * r->dir.y;
else
	wall_x = g->pl.pos.x + r->perp * r->dir.x;
wall_x -= floor(wall_x);
```

- Le point touché est `pos + perp × ray`.
- Face Est/Ouest (`hit_side == 0`) : le mur est une ligne verticale, la position **le long** du mur est la coordonnée **y**.
- Face Nord/Sud : la position le long du mur est **x**.
- `wall_x − floor(wall_x)` garde la partie après la virgule, dans `[0, 1)` : 0 = début de la case, 0.99 = fin.

## Quelle colonne de la texture : `tex_x`

```c
c->tex_x = (int)(wall_x * c->tex->w);
if (c->tex_x >= c->tex->w)
	c->tex_x = c->tex->w - 1;
if ((r->hit_side == 0 && r->dir.x < 0)
	|| (r->hit_side == 1 && r->dir.y > 0))
	c->tex_x = c->tex->w - 1 - c->tex_x;
```

**Le retournement.** On veut que la texture se lise **de gauche à droite pour le joueur**, sur toutes les faces.

| On regarde vers | la droite du joueur est | `wall_x` croît vers | retourner ? |
|---|---|---|---|
| Nord (`ray.y < 0`) | +x | la droite | non |
| Sud (`ray.y > 0`) | −x | la gauche | **oui** |
| Est (`ray.x > 0`) | +y | la droite | non |
| Ouest (`ray.x < 0`) | −y | la gauche | **oui** |

> [!warning] Ce n'est pas le code de lodev
> Le tutoriel de lodev a des conditions **inversées**, parce que son axe y monte. Ici y **descend** (sens du fichier et de l'écran). Copier ses conditions afficherait toutes les faces en miroir. Test : le tuyau des textures de démo doit être **à gauche** sur les 4 faces.

## Quelle ligne de la texture : `step` et `tex_pos`

```c
c->step = (double)c->tex->h / c->line_h;
c->tex_pos = (c->start - WIN_H / 2 + c->line_h / 2) * c->step;
```

- `step` : de combien on avance dans la texture pour **un** pixel d'écran. Un mur de 128 px avec une texture de 64 → `step = 0.5`, chaque texel est dessiné 2 fois.
- `tex_pos` : la ligne de texture du **premier** pixel dessiné.

| Situation | `start` | `tex_pos` initial |
|---|---|---|
| mur entier à l'écran | `WIN_H/2 − line_h/2` | `0` : on commence en haut de la texture |
| mur plus haut que l'écran | clampé à `0` | `(line_h/2 − WIN_H/2) × step` > 0 : on saute la partie cachée au-dessus de l'écran |

Sans ce décalage, quand on est près d'un mur, la texture commencerait toujours par sa première ligne : elle « glisserait » quand on avance.

## La colonne en une seule passe

```c
/* Une seule passe : chaque pixel est ecrit une fois (plafond, mur, sol) */
y = 0;
while (y < WIN_H)
{
	if (y < c.start)
		color = g->sc.ceil;
	else if (y > c.end)
		color = g->sc.floor;
	else
	{
		color = get_texel(c.tex, c.tex_x, (int)c.tex_pos);
		c.tex_pos += c.step;
	}
	put_pixel(&g->frame, x, y, color);
	y++;
}
```

```
 y = 0      ┌──┐
            │C │  plafond : g->sc.ceil
 start      ├──┤
            │▓▓│  mur : get_texel(tex, tex_x, tex_pos), tex_pos += step
 end        ├──┤
            │F │  sol : g->sc.floor
 WIN_H − 1  └──┘
```

> [!question] Pourquoi pas « remplir tout l'écran en plafond/sol, puis dessiner les murs » ?
> Ce serait écrire chaque pixel **deux fois**. En une passe, chaque pixel de la frame est écrit exactement une fois, et il n'y a pas besoin d'effacer la frame précédente : tout est réécrit.

## À retenir en 3 lignes

1. `hit_side` + signe du rayon → texture (NO = vue en regardant vers le Nord).
2. `wall_x` → `tex_x`, retourné quand on regarde vers le Sud ou l'Ouest (y descend : inverse de lodev).
3. `step = tex.h / line_h`, `tex_pos` commence au bon endroit quand le mur dépasse l'écran.

→ Suite : [09 - Boucle de jeu et mouvement](09%20-%20Boucle%20de%20jeu%20et%20mouvement.md)
