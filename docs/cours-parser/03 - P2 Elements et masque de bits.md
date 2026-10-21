---
tags: [cub3d, parsing, cours, P2]
---

# 03 · P2 Éléments et masque de bits

← [Index](00%20-%20Index.md) · Fichiers : `elements.c`, `parse_elements` dans `parse_scene.c`

## Le problème

Avant la map, le fichier contient 6 éléments (`NO SO WE EA F C`), **dans n'importe quel ordre**, séparés ou non par des lignes vides. Il faut :
- reconnaître chaque identifiant ;
- refuser les **doublons** et les **inconnus** ;
- savoir **exactement** où s'arrête la zone éléments, c'est-à-dire où commence la map.

## L'outil : un masque de bits `found`

`t_elem` numérote les éléments : `EL_NO = 0`, `EL_SO = 1`, … `EL_C = 5`. On réserve **un bit** par élément dans un seul `int` :

```
bit :      5   4   3   2   1   0
élément :  C   F   EA  WE  SO  NO
```

| Opération | Code | Exemple |
|---|---|---|
| marquer `el` comme vu | `found \|= 1 << el` | F vu : `found \|= 0b010000` |
| déjà vu ? (doublon) | `found & (1 << el)` | non nul → `E_DUP` |
| tous vus ? | `found == ALL_ELEMS` | `0b111111` = **63** |

> [!question] Pourquoi un masque et pas 6 booléens ?
> - **Une** variable au lieu de six, et **une** comparaison pour « tout est là ».
> - Le doublon se teste avec la même formule pour les 6 éléments : pas de `if/else` géant.
> - `el` sert à la fois d'indice de bit **et** d'indice dans `tex_path[el]` : tout est indexé par le même enum.

## La boucle de zone (`parse_elements`)

```c
while (g->sc.lines[i] && g->sc.found != ALL_ELEMS)
{
	if (!is_blank(g->sc.lines[i]))
		... parse_element(g, g->sc.lines[i]) ...
	i++;
}
if (g->sc.found != ALL_ELEMS)
	exit_game(g, 1, E_MISSING);
return (i);
```

> [!important] La zone se termine **exactement** quand le masque est plein
> On ne devine **pas** le début de la map en cherchant une ligne qui commence par `1`. Dès que les 6 éléments sont vus, la ligne non blanche suivante **est** la map, par définition. Conséquences :
> - `i_missing_C` : la ligne `111111` arrive alors qu'il manque C. `parse_element` voit un `1` et renvoie `E_MISSING`, ce qui est le **bon** message.
> - `i_element_after_map` : un `F` après la map n'est pas relu comme un élément (on a arrêté de chercher), c'est P5 qui le rejette (`E_MAPGAP`).

## `parse_element` ligne par ligne

```
"   F    220,100,0  "
 ^^^ ^ ^^^^^^^^^^^^^^
  │  │ └─ rest = line + i + len → transmis à P4
  │  └─ mot de longueur len = 1 → elem_id → EL_F
  └─ i = nombre d'espaces de tête (choix : acceptés)
```

Étapes et messages, **dans cet ordre** :

| # | Test | Message |
|---|---|---|
| 1 | la ligne contient `\t` ou `\r` | `E_BADSPACE` |
| 2 | mot inconnu **et** il commence par `0` ou `1` | `E_MISSING` (la map arrive trop tôt) |
| 3 | mot inconnu | `E_IDENT` |
| 4 | bit déjà levé | `E_DUP` |
| 5 | valeur invalide (P3 ou P4) | message de P3, ou `E_COLOR` |
| 6 | sinon | on lève le bit, `NULL` |

## `elem_id` : longueur **et** contenu

```c
if (len == 2 && !ft_strncmp(word, "NO", 2))
	return (EL_NO);
```

> [!warning] Le piège
> `ft_strncmp(line, "NO", 2)` seul accepte `NOX ./a.xpm` et `NO./a.xpm`. Ici `len` est la longueur du mot jusqu'au premier espace : `"NO./a.xpm"` a `len = 9`, ce qui donne -1 puis `E_IDENT`. C'est le cas `i_identifier_glued_to_path`.

Les minuscules (`no`) donnent aussi -1 → `E_IDENT` (`i_lowercase_identifier`).

## Pourquoi refuser `\t` et `\r` (choix)

- `\r` : un fichier enregistré sous Windows (CRLF) donne des lignes `"NO ./a.xpm\r"`. Sans ce test, on obtiendrait `E_TEXPATH` (le fichier `a.xpm\r` n'existe pas), un message **trompeur**. On préfère dire clairement « CRLF ? ».
- `\t` : le sujet parle d'espaces. Accepter les tabulations obligerait à les gérer partout (split, couleurs, map). On les refuse en un seul endroit.

> [!note] Le test ne porte que sur la zone éléments
> Une tabulation **dans la map** n'est pas vue ici (on s'est arrêté avant), c'est P6 qui la rejette avec `E_MAPCHAR` (`i_tab_in_map`).

## `parse_value` : le dispatch

```c
if (el <= EL_EA)
	return (parse_texture(g, el, rest));   /* P3 */
if (parse_rgb(rest, &color))               /* P4 */
	return (E_COLOR);
```

`el <= EL_EA` marche parce que l'enum range les 4 textures **avant** F et C. L'ordre de `t_elem` fait partie du contrat.

Le bit n'est levé **qu'après** une valeur valide. Ce n'est pas une nécessité (on quitte au premier échec), mais `found` reste ainsi toujours vrai : « bit levé ⇔ valeur stockée ».

## Cas à connaître par cœur

| Ligne | Résultat |
|---|---|
| `NO ./textures/test/no.xpm` | OK |
| `  F 1,2,3  ` | OK |
| `NOPE x` | `E_IDENT` |
| `F` | `E_COLOR` (rest = `""`, aucun chiffre) |
| `NO` | `E_TEXPATH` (0 mot) |
| `111111` (avant les 6) | `E_MISSING` |

Ces cas sont dans `tests/unit/t_elements.c`.

→ Suite : [04 - P3 Textures](04%20-%20P3%20Textures.md)
