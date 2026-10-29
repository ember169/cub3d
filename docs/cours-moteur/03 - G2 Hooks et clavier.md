---
tags: [cub3d, moteur, cours, G2]
---

# 03 · G2 Hooks et clavier

← [Index](00%20-%20Index.md) · Fichiers : `hooks.c`, `keys.c`

## Les cinq branchements

```c
mlx_hook(g->win, KeyPress, KeyPressMask, on_key_press, g);
mlx_hook(g->win, KeyRelease, KeyReleaseMask, on_key_release, g);
mlx_hook(g->win, FocusOut, FocusChangeMask, on_focus_out, g);
mlx_hook(g->win, DestroyNotify, 0, on_close, g);
mlx_loop_hook(g->mlx, game_loop, g);
```

| Événement X11 | Code | Handler | Rôle |
|---|---|---|---|
| `KeyPress` | 2 | `on_key_press(keysym, g)` | ESC → quitter ; sinon `keys[i] = 1` |
| `KeyRelease` | 3 | `on_key_release(keysym, g)` | `keys[i] = 0` |
| `FocusOut` | 10 | `on_focus_out(g)` | toutes les touches à 0 |
| `DestroyNotify` | 17 | `on_close(g)` | croix rouge → quitter |
| (boucle) | — | `game_loop(g)` | appelée à chaque tour de `mlx_loop` |

Le dernier argument (`g`) est passé tel quel au handler : c'est comme ça qu'un handler accède à tout le jeu sans variable globale.

## Décision n°1 : le handler clavier ne déplace pas le joueur

```c
/* On ne bouge pas ici : on note l'etat, game_loop fait le mouvement */
int	on_key_press(int keysym, t_game *g)
{
	...
	i = key_index(keysym);
	if (i >= 0)
		g->keys[i] = 1;
	return (0);
}
```

> [!question] Pourquoi un tableau `keys[]` plutôt que bouger dans le handler ?
> - `KeyPress` arrive **une fois**, puis la répétition automatique du clavier envoie des événements après un délai (~500 ms) et à un rythme qui dépend des réglages du système. Bouger dans le handler donne un démarrage saccadé et une vitesse différente sur chaque machine.
> - Avec un tableau, **plusieurs touches** marchent en même temps : avancer et tourner, avancer et faire un pas de côté.
> - Le mouvement se fait dans `game_loop`, une fois par frame, avec `dt` : la vitesse est régulière (voir [09](09%20-%20Boucle%20de%20jeu%20et%20mouvement.md)).

## Décision n°2 : pas de `mlx_key_hook`

Sous Linux, `mlx_key_hook` écoute **KeyRelease** (vérifié dans `mlx_key_hook.c`). Le handler ne serait appelé qu'au relâchement : impossible de savoir qu'une touche est tenue. On utilise donc `mlx_hook` avec les deux événements.

## `key_index` : un keysym → une case du tableau

```c
typedef enum e_key { K_W, K_A, K_S, K_D, K_LEFT, K_RIGHT, K_COUNT } t_key;
```

- `key_index` traduit `XK_w`, `XK_Left`… en indice 0 à 5. Une autre touche renvoie `-1` et est ignorée.
- `K_COUNT` vaut 6 **automatiquement** : ajouter une touche avant lui agrandit le tableau `keys[K_COUNT]` et la boucle de `on_focus_out` sans rien toucher d'autre.
- Les keysyms (`XK_w`…) viennent de `<X11/keysym.h>`. Ce sont des `#define`, pas des fonctions : leur usage est autorisé.

> [!note] Clavier AZERTY
> Les keysyms décrivent le **caractère**, pas la position physique. Sur un AZERTY, la touche marquée Z envoie `XK_z`, pas `XK_w`. Le sujet impose W A S D : en AZERTY, on appuie sur les touches marquées W, Q, S, D… ou on change le clavier en QWERTY. Passer en ZQSD est une modification live classique (voir [11](11%20-%20Soutenance.md)).

## Décision n°3 : remettre à zéro sur `FocusOut`

```c
/* Alt+Tab en tenant une touche : le KeyRelease part vers l'autre fenetre */
```

Scénario : tu tiens W, tu fais Alt+Tab vers le terminal, tu lâches W. Le `KeyRelease` est envoyé au **terminal**, pas à cub3D. Sans `FocusOut`, `keys[K_W]` reste à 1 et le joueur avance tout seul jusqu'au mur. Avec `FocusOut`, toutes les touches repassent à 0 dès qu'on perd le focus.

## ESC et la croix

| Action | Chemin | Code de sortie |
|---|---|---|
| ESC | `on_key_press` → `exit_game(g, 0, NULL)` | 0 |
| croix rouge | le gestionnaire de fenêtres envoie `WM_DELETE_WINDOW`, la MLX le traduit en `DestroyNotify` → `on_close` → `exit_game(g, 0, NULL)` | 0 |

`exit_game` est appelée **depuis l'intérieur** de `mlx_loop`. C'est sans danger : `exit` ne revient jamais, donc la MLX ne touche plus aux ressources qu'on vient de détruire.

> [!question] Pourquoi le masque de `DestroyNotify` vaut 0 ?
> La MLX traite `WM_DELETE_WINDOW` elle-même (dans `mlx_loop.c`) et appelle le hook enregistré sur l'événement 17, quel que soit le masque. `StructureNotifyMask` marcherait aussi.

## À retenir en 3 lignes

1. Les handlers ne font que noter l'état (`keys[i] = 0/1`) ; le mouvement est dans `game_loop`.
2. `mlx_hook` + KeyPress/KeyRelease, jamais `mlx_key_hook` (déclenché au relâchement sous Linux).
3. `FocusOut` vide le tableau : pas de touche « collée » après Alt+Tab.

→ Suite : [04 - G3 Textures XPM](04%20-%20G3%20Textures%20XPM.md)
