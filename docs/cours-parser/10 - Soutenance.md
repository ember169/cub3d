---
tags: [cub3d, parsing, cours, soutenance]
---

# 10 · Soutenance

← [Index](00%20-%20Index.md)

## Questions de correcteur → réponses courtes

> [!question]- Pourquoi tu lis tout le fichier avant de parser ?
> Pour distinguer une ligne vide **dans** la map d'une ligne vide **après** la map, il faut connaître la suite. Avec un tableau de lignes, je peux regarder en avant. Et je lis gnl jusqu'à `NULL`, donc son stash est toujours vidé.

> [!question]- Pourquoi pas `ft_split` sur `'\n'` ?
> Il fusionne les séparateurs : les lignes vides disparaissent, et une map coupée par une ligne vide serait acceptée.

> [!question]- Comment tu sais où commence la map ?
> Je ne le devine pas. Un masque de bits `found` note les éléments vus. Dès qu'il vaut 63 (les 6 bits), la ligne non blanche suivante **est** la map.

> [!question]- Comment tu détectes un doublon ?
> `found & (1 << el)` : si le bit de cet élément est déjà levé, c'est un doublon.

> [!question]- `NO./path.xpm` : accepté ?
> Non. Je compare la **longueur** du mot en plus du contenu. `NO./path.xpm` est un mot de 12 caractères, donc identifiant inconnu.

> [!question]- Pourquoi refuser les tabulations et `\r` ?
> `\r` vient d'un fichier CRLF : sans ce test, l'erreur serait « texture introuvable », ce qui est trompeur. Je préfère un message explicite. Les tabulations ne sont pas des espaces au sens du sujet, et les refuser à un seul endroit évite de les gérer partout.

> [!question]- Comment tu parses une couleur ? Pourquoi pas `atoi` ?
> Un automate : un indice avance de gauche à droite, et tout caractère inattendu est une erreur. `atoi` accepte `+` et `-`, déborde, et s'arrête en silence sur `22a`. `split` fusionne les virgules, donc `220,100,0,` passerait.

> [!question]- Et l'overflow sur `99999999999999999999` ?
> Impossible : je refuse dès que la valeur dépasse 255, **pendant** la lecture. Elle ne dépasse jamais 2 559.

> [!question]- Pourquoi compléter la map avec des espaces ?
> Pour pouvoir lire `grid[y][x]` partout sans tester la longueur de la ligne. Et parce qu'après la fin d'une ligne, c'est du vide, exactement comme un espace : une seule règle couvre les deux cas.

> [!question]- Comment tu vérifies que la map est fermée ?
> Chaque case marchable (`0` ou joueur) doit avoir ses 4 voisines dans la grille, et aucune ne doit être un espace. Le joueur et les rayons ne se déplacent que par les côtés des cases, donc si aucune case marchable ne touche le vide par un côté, on ne peut jamais l'atteindre.

> [!question]- Et les diagonales ?
> Pour passer en diagonale, il faut traverser une des deux cases adjacentes. Si la map est fermée, ce sont des murs.

> [!question]- Pourquoi pas un flood fill ?
> Récursif, il fait un appel par case : sur une grande map, ça déborde la pile (segfault). Il faut aussi copier la grille. Et il ignore les zones que le joueur ne peut pas atteindre. Ma règle n'a ni récursion ni allocation, et vérifie **toutes** les zones.

> [!question]- Un espace au milieu de la map, c'est valide ?
> Oui, si aucune case marchable ne le touche (`v_inner_void`). Le sujet dit que les espaces font partie de la map.

> [!question]- Pourquoi `+ 0.5` sur la position ?
> Pour placer le joueur au **centre** de sa case. Sinon il démarre dans un coin, collé à deux murs.

> [!question]- C'est quoi `plane` ?
> `dir` tourné de 90° vers la droite, multiplié par 0.66. Ça représente le bord droit de l'écran, et ça donne un FOV d'environ 66°.

> [!question]- Montre-moi qu'il n'y a pas de fuite si le malloc de la grille échoue.
> La grille est rattachée à `g` avant d'être remplie, et allouée avec `calloc`. `exit_game` appelle `free_tab`, qui libère les lignes déjà allouées et s'arrête au premier `NULL`.

> [!question]- Pourquoi tes fonctions renvoient un `char *` ?
> C'est le message d'erreur lui-même, un littéral : rien à allouer ni à libérer, et l'erreur remonte avec un simple `if (msg) return (msg);`. Seul `parse_scene` appelle `exit_game`, donc mes fonctions feuilles restent testables une par une.

> [!question]- Ta map contient deux îles fermées séparées. Accepté ?
> Oui (`v_two_islands`), parce que chacune est fermée. C'est un choix documenté.

## Les choix à annoncer (README → *Technical choices*)

- Extension `.cub` exacte, sensible à la casse.
- Espaces acceptés avant l'identifiant et en fin de ligne.
- Tabulation et `\r` refusés hors map, avec un message explicite.
- Couleur : espaces autour des virgules et zéros de tête acceptés ; `+`, hexadécimal, décimal refusés.
- Sol = plafond accepté.
- Textures : un seul chemin, `.xpm`, lisible ; chargement en G3.
- Lignes vides après la map tolérées, aucune dedans.
- Plusieurs zones fermées acceptées si chacune est fermée.
- Fermeture vérifiée par la règle des 4 voisins (pas de flood fill).

## Exercices pour vérifier que tu as compris

Fais-les **sans regarder le code**, puis vérifie.

1. **Prédire le message** que renvoie `parse_element` pour chaque ligne, avec `found = 0` :
   `"  C 0,0,0"` · `"EA"` · `"F 1,2"` · `"WE ./textures/test/we.xpm ./x.xpm"` · `"1111"` · `"SO\t./a.xpm"` · `"F  007 ,  8,9   "`
2. **Dessiner** la grille obtenue (avec les `·`) pour :
   ```
     111
   11101
   1N001
   11111
   ```
   Est-elle fermée ? Quelle case fautive `check_map` renvoie-t-elle (`row`, `col`) ?
3. **Casser volontairement** (branche jetable) : retire `len == 2 &&` dans `elem_id`. Quel message donne alors `i_identifier_glued_to_path` ? Pourquoi `run_tests.sh` ne verrait-il **pas** la régression ?
4. Un fichier contient les 6 éléments, puis `C 2,2,2`, puis la map. Quel message ? Pourquoi pas `E_DUP` ?
5. **Casser volontairement** : inverse l'ordre des tests dans `is_void` (`grid[y][x] == ' '` en premier). Compile avec `-fsanitize=address` et lance `i_open_top`. Qu'est-ce qui se passe ?
6. **Expliquer à voix haute**, en moins de 30 secondes chacune : `found`, `!tok[0] || tok[1]`, `rgb = (rgb << 8) | val`, `ft_calloc(h + 1, …)`.

> [!success]- Réponses de l'exercice 1
> OK (C noir) · `E_TEXPATH` · `E_COLOR` · `E_TEXPATH` (2 mots) · `E_MISSING` · `E_BADSPACE` · OK (`0x070809`)

> [!success]- Réponse de l'exercice 2
> Grille 5 × 4. La ligne 0 devient `··111`. Le `0` en (x=3, y=1) a pour voisin haut (3,0) = `1`, OK. Tous les `0` et le `N` sont entourés : la map est **fermée**. `check_map` renvoie 0.

> [!success]- Réponse de l'exercice 3
> `NO./textures/…` est reconnu comme `NO` (seuls les 2 premiers caractères sont comparés), et `rest` vaut `""` puisque `len` couvre tout le mot. On obtient `E_TEXPATH` au lieu de `E_IDENT`. `run_tests.sh` ne vérifie que la 1re ligne `Error`, pas le message : la régression passe inaperçue. D'où l'intérêt de `t_elements.c`, qui compare les messages.

> [!success]- Réponse de l'exercice 4
> `E_MAPCHAR`. Après les 6 éléments, la zone éléments est **fermée** : la ligne non blanche suivante (`C 2,2,2`) est le début de la map par définition. `C`, `,` et les chiffres autres que 0 et 1 ne sont pas des caractères de map. C'est la conséquence directe de « la zone se termine quand `found == 63` » (voir [03](03%20-%20P2%20Elements%20et%20masque%20de%20bits.md)).

## Lancer les tests

```bash
bash tests/gen_maps.sh          # attention : efface et régénère maps/ et textures/test
make && bash tests/run_tests.sh
VG=1 bash tests/run_tests.sh    # + valgrind
```

Tant que G3 et la fenêtre ne sont pas faits, il reste **22 KO attendus** : `i_texture_corrupted`, `i_texture_empty_file` (rejetés en G3) et les 20 valides (qui doivent ouvrir une fenêtre).
