---
tags: [cub3d, parsing, cours, P8]
---

# 08 · P8 Initialisation du joueur

← [Index](00%20-%20Index.md) · Fichier : `player.c`

## Pourquoi P8 ne peut pas échouer

P6 a déjà garanti qu'il y a **exactement un** joueur. P8 n'a donc aucun cas d'erreur, et sa signature est `void`. C'est un bénéfice direct du pipeline : chaque étape fait confiance aux précédentes.

## Le repère

```
        x →  (Est)
      0 1 2 3
  y 0 1 1 1 1
  ↓ 1 1 N 0 1      N en (x=2, y=1)
    2 1 1 1 1
  (Sud)
```

**`y` va vers le bas**, donc le Nord correspond à `y` négatif. C'est le sens de lecture du fichier (ligne 0 en haut).

## Ce qu'on calcule

| Champ | Valeur | Pourquoi |
|---|---|---|
| `pos` | `(x + 0.5, y + 0.5)` | **centre** de la case. Sans `+ 0.5`, le joueur démarre dans un coin, à cheval sur deux murs. |
| `dir` | N `(0,-1)` · S `(0,1)` · E `(1,0)` · W `(-1,0)` | vecteur unitaire de la direction du regard |
| `plane` | `(-dir.y, dir.x) × FOV_PLANE` | bord droit de l'écran (voir ci-dessous) |
| `grid[y][x]` | remplacé par `'0'` | le rendu et les collisions ne voient plus qu'une case vide |

## `plane` en une phrase

`plane` est `dir` **tourné de 90° vers la droite**, mis à l'échelle du champ de vision.

Tourner `(x, y)` de +90° (sens horaire à l'écran, puisque y descend) donne `(-y, x)`.

| Spawn | `dir` | `plane` | Vérification |
|---|---|---|---|
| N | (0, -1) | (0.66, 0) | face au Nord, la droite est l'Est (+x) ✔ |
| S | (0, 1) | (-0.66, 0) | face au Sud, la droite est l'Ouest ✔ |
| E | (1, 0) | (0, 0.66) | face à l'Est, la droite est le Sud (+y) ✔ |
| W | (-1, 0) | (0, -0.66) | face à l'Ouest, la droite est le Nord ✔ |

**Pourquoi 0.66** : le FOV vaut `2 × atan(0.66 / 1) ≈ 66°`, un champ de vision proche de celui de Wolfenstein 3D.

> [!warning] Signe de `plane`
> Une erreur de signe ne plante pas : elle **inverse le monde** (miroir). Tourner à droite fait alors défiler l'image dans le mauvais sens. Si ça arrive à l'intégration, regarde `set_dir` en premier.

## Pourquoi remplacer la lettre par `'0'`

Après P8, la position du joueur vit dans `g->pl.pos`. Si on laissait `N` dans la grille, le DDA, les collisions et la minimap devraient tous savoir que `N` est « du vide ». Avec `'0'`, il n'y a plus de cas particulier.

## Vérifier

```
$ ./t_parse maps/valid/v_facing_E.cub
...
pos   (2.50, 2.50)
dir   (1.00, 0.00)
plane (0.00, 0.66)
```

→ Suite : [09 - Memoire et erreurs](09%20-%20Memoire%20et%20erreurs.md)
