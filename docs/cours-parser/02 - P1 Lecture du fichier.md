---
tags: [cub3d, parsing, cours, P1]
---

# 02 · P1 Lecture du fichier

← [Index](00%20-%20Index.md) · Fichiers : `file.c`, `read_line.c`, début de `parse_scene.c`

## Ce que fait P1

1. `check_extension(path, ".cub")` : le **nom de base** se termine exactement par `.cub` et fait plus de 4 caractères.
2. `check_readable_file(path)` : 0 = OK, 1 = c'est un dossier, 2 = impossible à ouvrir.
3. `read_lines(path, &err)` : tout le fichier dans un `char **` terminé par `NULL`, **sans les `\n`**, en gardant **les lignes vides**.
4. `all_blank(lines)` : un fichier vide ou rempli d'espaces donne `E_EMPTY`.

## Pourquoi lire TOUT le fichier avant de parser

> [!important] L'argument clé
> Pour savoir si une ligne vide est **dans** la map (erreur) ou **après** la map (toléré), il faut connaître **la suite**. Avec un tableau de lignes, on peut regarder en avant, et chaque étape reçoit simplement « l'indice où commencer ».

Deuxième raison : on appelle `get_next_line` **jusqu'à ce qu'il renvoie `NULL`**, même après une erreur. Son buffer statique (le *stash*) est donc toujours vidé, et valgrind n'affiche aucun bloc *still reachable*. C'est le rôle de `push_all_lines` :

```c
line = get_next_line(fd);
while (line)
{
	...                               /* retirer le '\n' final */
	if (*err || tab_push(tab, line))  /* après une erreur : on lit, on jette */
	{
		*err = 1;
		free(line);
	}
	line = get_next_line(fd);
}
```

## Le piège n°1 du parsing cub3D : `ft_split(contenu, '\n')`

`ft_split` **fusionne les séparateurs** : `"111\n\n101"` donne `["111", "101"]`. La ligne vide disparaît, et `i_empty_line_inside_map` devient valide. C'est pour ça qu'on lit **ligne par ligne** avec gnl.

## `tab_push` : un tableau qui grandit

À chaque ligne : on alloue `n + 2` pointeurs (les anciens, le nouveau, et `NULL`), on copie, puis on libère **l'ancien tableau seulement** (pas les chaînes, qui sont déplacées). C'est du O(n²) en copies, mais pour un fichier de quelques centaines de lignes c'est négligeable, et c'est simple à prouver correct.

## Détecter un dossier sans `stat`

`stat` n'est pas autorisé par le sujet. Astuce : `open(path, O_RDONLY | O_DIRECTORY)` **échoue sur tout ce qui n'est pas un dossier**. S'il réussit, c'est un dossier.

> [!warning] Pourquoi c'est nécessaire
> Sous Linux, `open("dossier", O_RDONLY)` **réussit**. C'est `read` qui échoue ensuite, gnl renvoie `NULL`, et le dossier ressemble alors à un fichier vide (`E_EMPTY` au lieu de `E_ISDIR`).

## `check_extension` compare la **fin** du nom de base

| Entrée | Résultat | Pourquoi |
|---|---|---|
| `maps/a.cub` | ✅ | |
| `maps/.cub` | ❌ | nom de base `.cub` : longueur 4, pas > 4 |
| `a.cub.txt` | ❌ | ne **finit** pas par `.cub` (`ft_strnstr` l'aurait accepté) |
| `a.CUB` | ❌ | choix : sensible à la casse |
| `""` | ❌ | longueur 0 |

`ft_strrchr(path, '/')` donne le nom de base, ce qui permet à `dossier.cub/carte` d'être bien rejeté.

## `is_blank` : la définition de « ligne vide »

Vide **ou** composée uniquement d'espaces (choix documenté). Une tabulation n'est **pas** un blanc : une ligne `"\t"` sera traitée comme du contenu, puis rejetée (`E_BADSPACE` ou `E_MAPCHAR`).

## Erreurs produites

| Cas | Message |
|---|---|
| pas `.cub` | `E_EXT` |
| dossier | `E_ISDIR` |
| inexistant / pas les droits | `E_OPEN` |
| malloc raté pendant la lecture | `E_MALLOC` |
| vide ou que des blancs | `E_EMPTY` |

→ Suite : [03 - P2 Elements et masque de bits](03%20-%20P2%20Elements%20et%20masque%20de%20bits.md)
