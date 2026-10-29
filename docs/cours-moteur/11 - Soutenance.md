---
tags: [cub3d, moteur, cours, soutenance]
---

# 11 · Soutenance

← [Index](00%20-%20Index.md) · Questions sur le parser : [cours-parser/10](../cours-parser/10%20-%20Soutenance.md)

## Questions de correcteur → réponses courtes

### MiniLibX

> [!question]- Pourquoi une image et pas `mlx_pixel_put` ?
> `mlx_pixel_put` envoie une requête X11 par pixel : 691 200 par frame, et on voit l'image se dessiner. J'écris dans une image en mémoire, puis un seul `mlx_put_image_to_window` affiche la frame entière.

> [!question]- Explique `addr + y * line_len + x * (bpp / 8)`.
> `line_len` = octets par ligne (padding compris), `bpp / 8` = octets par pixel. On calcule en `char *` pour compter en octets, puis on écrit les 4 octets avec un `unsigned int *`.

> [!question]- Pourquoi ne pas utiliser `w * 4` au lieu de `line_len` ?
> La MLX peut ajouter du padding en fin de ligne. Avec `w * 4`, chaque ligne serait décalée et l'image penchée.

> [!question]- Comment tu gères les touches maintenues ?
> Les handlers KeyPress/KeyRelease mettent `keys[i]` à 1 ou 0. Le mouvement se fait dans `game_loop`, une fois par frame. Plusieurs touches marchent en même temps, et la vitesse ne dépend pas de la répétition automatique du clavier.

> [!question]- Pourquoi pas `mlx_key_hook` ?
> Sous Linux, il écoute KeyRelease : on ne saurait pas qu'une touche est tenue.

> [!question]- Je tiens W et je fais Alt+Tab. Que se passe-t-il ?
> Le KeyRelease part vers l'autre fenêtre. Mon hook `FocusOut` remet toutes les touches à 0 : le joueur s'arrête.

> [!question]- Comment fonctionne la croix rouge ?
> Le gestionnaire de fenêtres envoie `WM_DELETE_WINDOW`, la MLX appelle le hook enregistré sur `DestroyNotify` (17). Mon handler appelle `exit_game(g, 0, NULL)`.

> [!question]- Pourquoi tu charges les textures avant d'ouvrir la fenêtre ?
> Une texture invalide fait quitter. Dans cet ordre, aucune fenêtre n'apparaît pour disparaître aussitôt.

> [!question]- Dans quel ordre tu libères la MLX ?
> Images, fenêtre, `mlx_destroy_display`, puis `free(g->mlx)`. L'inverse de la création : les images et la fenêtre ont besoin de la connexion X. `mlx_destroy_display` ne libère pas la structure allouée par `mlx_init`.

### Raycasting

> [!question]- C'est quoi le raycasting ? C'est de la 3D ?
> Un rayon par colonne d'écran dans une grille 2D. La distance au premier mur donne la hauteur de la colonne. C'est de la 2,5D : murs verticaux, tous de la même hauteur, pas de vraie géométrie 3D.

> [!question]- Pourquoi `dir` + `plane` et pas un angle ?
> Un rayon = `dir + plane × camera_x` : deux multiplications, aucun `cos` ni `sin`. La trigonométrie ne sert qu'à tourner `dir` et `plane`, une fois par frame.

> [!question]- Comment se calcule le FOV ? Comment le changer ?
> `FOV = 2 × atan(|plane|)`, avec `|dir| = 1`. 0.66 donne environ 66°. Pour 90°, `FOV_PLANE = 1.0`.

> [!question]- Explique le DDA.
> On avance de ligne de grille en ligne de grille. `delta` = le `t` pour traverser une case, `side` = le `t` jusqu'à la prochaine ligne dans chaque axe. On franchit toujours la plus proche, donc on visite chaque case traversée, sans en sauter aucune. On s'arrête sur une case solide.

> [!question]- Et si `ray.x == 0` ?
> `delta.x = 1e30` : le rayon ne franchit jamais de ligne verticale, la comparaison choisit toujours y. Pas de division par zéro.

> [!question]- Le DDA peut-il boucler à l'infini ?
> Non. La map est fermée, et `is_solid` renvoie 1 hors de la grille : le rayon s'arrête au plus tard au bord.

> [!question]- Pourquoi n'y a-t-il pas d'effet fisheye ?
> `perp = side − delta` est le `t` du point touché. Comme le rayon n'est pas normalisé, sa composante le long de `dir` vaut 1 : ce `t` est la profondeur le long de `dir`, pas la longueur du rayon. Un mur droit reste droit.

> [!question]- Pourquoi `side − delta` ?
> Au dernier tour du DDA, on a ajouté un `delta` pour préparer le franchissement suivant, qui n'a jamais eu lieu. On le retire.

> [!question]- Que se passe-t-il collé contre un mur ?
> `perp` est ramené à `MIN_PERP` (0.0001) : pas de division par 0. `start` et `end` sont ramenés dans l'écran, et `tex_pos` commence au bon endroit de la texture.

> [!question]- Comment tu choisis la texture ?
> `hit_side` dit si on a touché une face Est/Ouest (0) ou Nord/Sud (1), le signe du rayon dit dans quel sens on regarde. NO = la texture vue en regardant vers le Nord.

> [!question]- Pourquoi retourner `tex_x` ?
> Pour que la texture se lise de gauche à droite **pour le joueur** sur toutes les faces. Quand on regarde vers le Sud ou l'Ouest, `wall_x` croît vers la gauche du joueur : on retourne. Les conditions sont l'inverse de celles de lodev, parce que mon y descend.

> [!question]- À quoi sert `tex_pos` initial ?
> Quand le mur est plus haut que l'écran, `start` est clampé à 0. `tex_pos` saute la partie de la texture cachée au-dessus de l'écran ; sinon la texture glisserait quand on avance.

### Boucle et mouvement

> [!question]- Pourquoi le jeu va à la même vitesse sur toutes les machines ?
> Les déplacements sont multipliés par `dt`, le temps écoulé depuis la frame précédente : la vitesse est en cases par seconde, pas en cases par frame.

> [!question]- À quoi sert `MAX_DT` ?
> Après une pause (gdb, fenêtre gelée), `dt` pourrait valoir plusieurs secondes et téléporter le joueur à travers un mur. Avec `MAX_DT = 0.05`, le pas maximal vaut 3.0 × 0.05 = 0.15 case, toujours moins d'une case.

> [!question]- Pourquoi `old` dans la rotation ?
> La 2e ligne a besoin de l'**ancien** `dir.x`. Sans `old`, elle utiliserait le nouveau et la caméra se déformerait.

> [!question]- Il y a des collisions dans ton mandatory ?
> Une collision minimale : le point `pos` n'entre jamais dans une case solide, testé axe par axe. Ce n'est pas une fonctionnalité, c'est ce qui empêche de sortir de la map et de lire `grid` hors limites. La vraie collision (avec un rayon autour du joueur) est le bonus.

> [!question]- Pourquoi tu redessines à chaque tour ?
> L'image revient seule après une minimisation, il n'y a pas de drapeau à gérer, et 960 rayons par frame ne coûtent presque rien.

### Build

> [!question]- Pourquoi `-std=gnu17` ?
> GCC 15 compile en C23 par défaut. En C23, `int (*)()` veut dire « sans paramètre », et nos handlers passés à `mlx_hook` sont refusés. `gnu17` rétablit l'ancien sens.

> [!question]- Ton Makefile relink ?
> Non : si aucun `.o` n'a changé et que `libmlx.a` et `libft.a` existent, `make` ne fait rien.

## Modifications live : où et quoi

| Demande | Où | Quoi | Piège |
|---|---|---|---|
| Fenêtre 1280 × 720 | `cub3d.h` | `WIN_W 1280` et `FOV_PLANE 0.89` | sans changer le FOV, les murs paraissent écrasés ; `make re` (header non suivi) |
| FOV de 90° | `cub3d.h` | `FOV_PLANE 1.0` | c'est `|plane|` qu'on règle, pas un angle |
| Aller 2× plus vite | `cub3d.h` | `MOVE_SPEED 6.0` | garder `MOVE_SPEED × MAX_DT < 1` |
| Touches ZQSD | `core/gfx/keys.c` | `XK_z`, `XK_q` dans `key_index` | les keysyms sont en minuscules |
| Inverser les flèches | `update_player` | signe de `rot` | — |
| Convention « NO = face orientée au Nord » | `mandatory/rules.c` | échanger NO↔SO et EA↔WE dans `select_texture` | le retournement de `tex_x` ne change **pas** : il dépend du rayon |
| Assombrir les faces N/S | `core/render/column.c` | si `hit_side == 1` : `color = (color >> 1) & 0x7F7F7F` | le masque empêche un canal de déborder sur le voisin |
| Afficher les FPS | `mandatory/loop.c` | `mlx_string_put` **après** `mlx_put_image_to_window`, texte = `ft_itoa(1 / dt)` | `free` le texte à chaque frame |
| Limiter à 30 FPS | `mandatory/loop.c` | si `now − last_time < 1 / 30.0` : `return (0)` | ne pas mettre à jour `last_time` dans ce cas ; `usleep` interdit |
| Nouveau caractère `2` = mur | `mandatory/rules.c` | `is_map_char` et `is_solid` | ne pas l'ajouter à `is_walkable` |
| Désactiver les collisions | `update_player` | `pos += d` sans test | pas de crash grâce aux bornes de `is_solid`, mais on voit « dans » le mur |

## Exercices pour vérifier que tu as compris

Fais-les **sans regarder le code**, puis vérifie.

1. Joueur en `(1.5, 1.5)`, `dir = (0, −1)`, `plane = (0.66, 0)`. Calcule le rayon de la colonne 0, de la colonne 480 et de la dernière colonne (959).
2. Pour le rayon `(0.5, −1)` depuis `(1.5, 1.5)` : calcule `delta`, `step` et `side` initiaux, puis les 3 premiers tours du DDA.
3. `perp = 0.5`, `WIN_H = 720` : calcule `line_h`, `start`, `end`, puis `tex_pos` initial pour une texture 64 × 64.
4. Un rayon `(−0.3, 1)` touche une face avec `hit_side = 1`. Quelle texture ? Faut-il retourner `tex_x` ?
5. **Casser volontairement** (branche jetable) : remplace `2.0` par `2` dans `cast_ray`. Prédis l'image, puis lance.
6. **Casser volontairement** : retire `old` dans la rotation. Tourne 10 secondes. Que voit-on, et pourquoi ?
7. **Expliquer à voix haute**, en moins de 30 secondes chacune : `delta`, `side − delta`, `tex_pos`, `MAX_DT`, `FocusOut`.

> [!success]- Réponse de l'exercice 1
> `camera_x` vaut −1, 0 et 2 × 959 / 960 − 1 ≈ 0.998. Rayons : `(−0.66, −1)`, `(0, −1)`, `(≈0.659, −1)`. Le rayon du milieu est exactement `dir`.

> [!success]- Réponse de l'exercice 2
> `delta = (1 / 0.5, 1 / 1) = (2, 1)`. `step = (+1, −1)`. `side.x = (2 − 1.5) × 2 = 1`, `side.y = (1.5 − 1) × 1 = 0.5`.
> Tour 1 : 1 ≥ 0.5 → y, `side = (1, 1.5)`, case (1, 0). Tour 2 : 1 < 1.5 → x, `side = (3, 1.5)`, case (2, 0). Tour 3 : 3 ≥ 1.5 → y, `side = (3, 2.5)`, case (2, −1) (hors grille → solide, on s'arrête). Dans une vraie map fermée, la ligne 0 est faite de `1` : on s'arrête dès le tour 1 avec `hit_side = 1`, `perp = 1.5 − 1 = 0.5`.

> [!success]- Réponse de l'exercice 3
> `line_h = 1440`, `start = 360 − 720 = −360` → clampé à 0, `end = 360 + 720 = 1080` → clampé à 719. `step = 64 / 1440 ≈ 0.0444`. `tex_pos = (0 − 360 + 720) × 0.0444 = 16` : on commence à la ligne 16 de la texture, le quart du haut est hors écran.

> [!success]- Réponse de l'exercice 4
> `hit_side = 1` et `ray.y > 0` : on regarde vers le Sud → `SO`. On retourne `tex_x` (`hit_side == 1 && ray.y > 0`).

> [!success]- Réponse de l'exercice 5
> `2 * x / WIN_W` vaut 0 pour toutes les colonnes (division entière), donc `camera_x = −1` partout : chaque colonne affiche le rayon du bord gauche, l'écran est fait de bandes verticales identiques.

> [!success]- Réponse de l'exercice 6
> `dir` et `plane` perdent leur longueur et leur angle droit. Le FOV change, les murs se déforment et la caméra finit par s'écraser. Le calcul de `dir.y` utilise un `dir.x` déjà tourné : ce n'est plus une rotation.
