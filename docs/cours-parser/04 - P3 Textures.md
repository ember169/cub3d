---
tags: [cub3d, parsing, cours, P3]
---

# 04 · P3 Textures

← [Index](00%20-%20Index.md) · Fichier : `texture_path.c`

## Ce que fait `parse_texture(g, el, rest)`

Il **valide** le chemin et en stocke une **copie** dans `g->sc.tex_path[el]`. Il ne charge pas l'image : ça se fait en G3 avec la MLX.

```c
tok = ft_split(rest, ' ');
if (!tok)
	return (E_MALLOC);
msg = NULL;
if (!tok[0] || tok[1])                         /* pas exactement 1 mot */
	msg = E_TEXPATH;
else if (!check_extension(tok[0], ".xpm"))
	msg = E_TEXPATH;
else if (check_readable_file(tok[0]) != 0)     /* dossier, absent, illisible */
	msg = E_TEXPATH;
else
{
	g->sc.tex_path[el] = ft_strdup(tok[0]);
	if (!g->sc.tex_path[el])
		msg = E_MALLOC;
}
free_tab(tok);
return (msg);
```

## Trois idées à savoir expliquer

### 1. « Exactement un mot » en une ligne : `!tok[0] || tok[1]`

`ft_split` renvoie un tableau terminé par `NULL`.
- 0 mot (`"NO"` seul) : `tok[0] == NULL`.
- 2 mots ou plus : `tok[1] != NULL`.

Pas besoin d'une fonction pour compter. Comme `ft_split` sur `' '` fusionne les espaces, `"NO    ./a.xpm   "` donne bien un seul mot (`v_extra_spaces_elements`).

### 2. Un seul point de sortie après le split

Toutes les branches arrivent à `free_tab(tok)`. Il est donc **impossible** d'oublier de libérer `tok` dans un cas d'erreur. Avec des `return` dans chaque `if`, il faudrait répéter `free_tab(tok)` quatre fois, et un oubli fait une fuite.

### 3. `ft_strdup(tok[0])`, pas `tok[0]`

`tok[0]` est libéré par `free_tab(tok)`. Stocker le pointeur directement laisserait un **pointeur pendant** (*dangling pointer*) : *use-after-free* en G3, puis *double free* dans `exit_game`.

## Pourquoi vérifier l'extension `.xpm` (choix)

La MLX ne regarde pas l'extension : elle lit le contenu. Mais un fichier `north.png` qui contient du XPM est une **incohérence**, et un correcteur peut la tester (`i_texture_bad_extension`). On exige donc un format explicite.

## Pourquoi ne pas charger la texture ici

| Raison | Détail |
|---|---|
| Tests sans écran | Le parsing tourne sans serveur X : les tests de A n'ont pas besoin de fenêtre. |
| Ordre | Un fichier invalide est rejeté **avant** `mlx_init`, donc on n'ouvre jamais de connexion X pour rien. |
| Séparation A / B | P3 valide (A), G3 charge (B). L'interface entre les deux est `tex_path[4]`. |

Conséquence assumée : `i_texture_corrupted` et `i_texture_empty_file` **passent** P3 (le fichier existe, il est lisible et finit par `.xpm`) et sont rejetés en G3 avec `E_TEXLOAD`.

> [!tip] Chemin relatif
> `./textures/test/no.xpm` se résout depuis le **répertoire courant**, pas depuis l'emplacement du `.cub`. Lance donc `./cub3D` depuis la racine du repo.

## Erreurs produites

| Fichier de test | Pourquoi |
|---|---|
| `i_texture_no_path` | 0 mot |
| `i_texture_two_paths` | 2 mots |
| `i_texture_not_found` | `open` échoue (2) |
| `i_texture_is_directory` | `O_DIRECTORY` réussit (1) |
| `i_texture_bad_extension` | `.png` |
| `i_texture_no_permission` | `open` échoue (2) |

→ Suite : [05 - P4 Couleurs (automate)](05%20-%20P4%20Couleurs%20(automate).md)
