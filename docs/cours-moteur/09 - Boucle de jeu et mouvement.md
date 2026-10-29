---
tags: [cub3d, moteur, cours, I1, M1, M2]
---

# 09 · Boucle de jeu et mouvement

← [Index](00%20-%20Index.md) · Fichiers : `loop.c`, `temp_move.c` ⚠️

> [!warning] État actuel
> `now_seconds` et `update_player` sont dans `mandatory/temp_move.c`, un remplaçant **provisoire** écrit pour tester le rendu. Le module M (`core/move/`) n'est pas encore écrit. Cette page décrit ce qui tourne aujourd'hui et ce qui doit changer. Quand `core/move/` arrive, il faut **retirer `temp_move.c` des SRCS** (sinon : symboles en double au lien).

## `game_loop` : une frame

```c
/* Redessine a chaque tour : l'image revient seule apres minimisation.
** dt plafonne : une frame tres lente (valgrind) ne traverse pas un mur */
int	game_loop(t_game *g)
{
	t = now_seconds();
	dt = t - g->last_time;
	g->last_time = t;
	if (dt > MAX_DT)
		dt = MAX_DT;
	update_player(g, dt);
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.ptr, 0, 0);
	return (0);
}
```

> [!question] Pourquoi redessiner à chaque tour, même si rien ne bouge ?
> - Après une minimisation ou si une autre fenêtre passe devant, l'image revient toute seule au tour suivant. Pas besoin de hook `Expose`.
> - Le code est plus simple : pas de drapeau « la scène a changé ».
> - Le coût (960 rayons) est négligeable sur une machine actuelle.

## Décision : la vitesse dépend du temps, pas du nombre de frames

| | `pos += 0.05` par frame | `pos += MOVE_SPEED × dt` (**choix**) |
|---|---|---|
| machine rapide vs lente (valgrind, `-fsanitize`) | le joueur file ou rampe | même vitesse en cases/seconde |
| grande map, plus de calcul par frame | le joueur ralentit | ne change rien |

- `dt` = temps écoulé depuis la frame précédente, en secondes.
- `MOVE_SPEED = 3.0` cases/s, `ROT_SPEED = 2.5` rad/s (un tour complet ≈ 2,5 s).

### Le plafond `MAX_DT = 0.05`

Après une pause (arrêt sous gdb, fenêtre gelée), `dt` pourrait valoir plusieurs secondes : le joueur se téléporterait, éventuellement **de l'autre côté d'un mur**. Avec le plafond, le pas maximal par frame vaut :

```
MOVE_SPEED × MAX_DT = 3.0 × 0.05 = 0.15 case  <  1
```

Un pas plus petit qu'une case ne peut pas sauter par-dessus un mur entier. Si on augmente `MOVE_SPEED`, il faut garder ce produit **< 1**.

### `now_seconds`

```c
gettimeofday(&tv, NULL);
return (tv.tv_sec + tv.tv_usec / 1000000.0);
```

`gettimeofday` est autorisée par le sujet. Le `.0` est indispensable : `tv_usec / 1000000` en entier vaudrait toujours 0.

## La rotation (← →)

```c
rot = (g->keys[K_RIGHT] - g->keys[K_LEFT]) * ROT_SPEED * dt;
```

`keys[]` vaut 0 ou 1 : la différence donne +1 (droite), −1 (gauche) ou 0 (aucune ou les deux). On tourne `dir` **et** `plane` du même angle, avec la matrice de rotation 2D :

```c
old = p->dir.x;
p->dir.x = p->dir.x * cos(a) - p->dir.y * sin(a);
p->dir.y = old * sin(a) + p->dir.y * cos(a);
/* même chose pour plane */
```

| Piège | Conséquence |
|---|---|
| oublier `old` | la 2e ligne utilise le **nouveau** `dir.x` : la caméra se déforme en quelques tours |
| tourner `dir` sans `plane` | `plane` n'est plus perpendiculaire : le monde se tord |
| angle en degrés | `cos` et `sin` attendent des radians |

Un angle **positif** tourne vers la droite, parce que y descend (le sens trigonométrique « mathématique » apparaît horaire à l'écran).

## Le déplacement (W A S D)

Version TEMP actuelle :

```c
fwd = (g->keys[K_W] - g->keys[K_S]) * MOVE_SPEED * dt;
side = (g->keys[K_D] - g->keys[K_A]) * MOVE_SPEED * dt;
len = |plane|;
temp_move(g, dir.x * fwd + plane.x / len * side,
	dir.y * fwd + plane.y / len * side);
```

- W/S avancent selon `dir` (longueur 1).
- A/D font un pas de côté selon `plane` **normalisé** (`plane / |plane|`). Sans la division, le pas de côté serait 0.66 fois plus lent que la marche.

## La collision (mandatory)

```c
/* TEMP : collision axe par axe, sans marge */
if (!is_solid(g, (int)(pos.x + dx), (int)pos.y))
	pos.x += dx;
if (!is_solid(g, (int)pos.x, (int)(pos.y + dy)))
	pos.y += dy;
```

- On teste x, puis y, **séparément**. Contre un mur en biais, la composante parallèle au mur passe : le joueur **glisse** au lieu d'être bloqué net.
- Un coin ne peut pas être traversé en diagonale : chaque axe est validé seul.

> [!question] Les collisions ne sont-elles pas un bonus ?
> Le sujet range « wall collisions » dans les bonus. Mais il exige aussi que le programme ne crashe jamais : sans aucune collision, le joueur sortirait de la map et `grid[y][x]` serait lu hors limites. Le mandatory a donc une collision **minimale** : le **point** `pos` n'entre jamais dans une case solide. Le bonus B1 ajoutera une vraie collision avec un rayon autour du joueur (on ne colle plus le nez aux murs).

## Ce qu'il reste à faire pour M1 / M2

| À faire | Pourquoi |
|---|---|
| créer `core/move/` avec `now_seconds`, `update_player`, `rotate_player` | prototypes déjà déclarés dans `cub3d.h` |
| sortir la collision dans `try_move` (`mandatory/collide.c`) | point de variation : le bonus B1 la remplacera |
| **normaliser le vecteur de déplacement total** | aujourd'hui, W + D donne un vecteur de longueur √2 : le joueur va **41 % plus vite** en diagonale. Il faut additionner les directions, puis diviser par la longueur (si elle n'est pas nulle). |
| retirer `temp_move.c` des SRCS | sinon doublon de symboles |

Tests manuels attendus : W+D pas plus rapide que W ; foncer dans chaque mur et chaque coin sans traverser ; Alt+Tab en avançant → le joueur s'arrête ; un tour complet prend ≈ 2,5 s, à la maison comme sous valgrind.

## À retenir en 3 lignes

1. Une frame = temps → mouvement → rendu → affichage, à chaque tour de `mlx_loop`.
2. Vitesse × `dt`, avec `dt ≤ MAX_DT` : même vitesse partout, pas d'effet tunnel.
3. Collision du point, axe par axe : on glisse le long des murs, on ne sort jamais de la map.

→ Suite : [10 - Build, tests et ressources](10%20-%20Build%2C%20tests%20et%20ressources.md)
