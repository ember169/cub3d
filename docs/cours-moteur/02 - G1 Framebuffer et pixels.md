---
tags: [cub3d, moteur, cours, G1]
---

# 02 · G1 Framebuffer et pixels

← [Index](00%20-%20Index.md) · Fichiers : `gfx_init.c`, `pixel.c`

## Le problème : `mlx_pixel_put` est inutilisable

`mlx_pixel_put` envoie **une requête X11 par pixel**. Une frame de 960 × 720, c'est 691 200 requêtes, envoyées une par une au serveur X, et affichées au fur et à mesure : l'image se dessine sous tes yeux et scintille.

## La solution : dessiner dans une image, l'afficher d'un coup

```c
g->frame.ptr = mlx_new_image(g->mlx, WIN_W, WIN_H);
g->frame.addr = mlx_get_data_addr(g->frame.ptr, &g->frame.bpp,
		&g->frame.line_len, &g->frame.endian);
```

- `frame` est un **tableau d'octets en mémoire**. Écrire dedans ne coûte rien, il n'y a aucun échange avec le serveur X.
- À la fin de la frame, **un seul** `mlx_put_image_to_window` envoie l'image complète.
- Résultat : on ne voit jamais une image à moitié dessinée. C'est du double buffering, sans le dire.

## `t_img` : ce que renvoie `mlx_get_data_addr`

| Champ | Sens | Valeur typique |
|---|---|---|
| `addr` | adresse du premier octet du pixel (0, 0) | — |
| `bpp` | **bits** par pixel | 32 |
| `line_len` | **octets** par ligne | ≥ `w × 4` |
| `endian` | ordre des octets | ignoré (serveur et programme sur la même machine) |
| `w`, `h` | taille : la MLX ne la renvoie pas pour `mlx_new_image`, on la stocke nous-mêmes | `WIN_W`, `WIN_H` |

## `put_pixel` : l'adresse d'un pixel

```c
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
```

```
addr ─►┌────┬────┬────┬─ … ─┬────┬ padding ┐   ligne 0 : line_len octets
       │ p0 │ p1 │ p2 │     │pw-1│         │
       ├────┼────┼────┼─ … ─┼────┼─────────┤   ligne 1 commence à addr + line_len
       │    │    │    │     │    │         │
```

| Morceau | Pourquoi |
|---|---|
| `y * line_len` | sauter `y` lignes **complètes**, padding compris |
| `x * (bpp / 8)` | sauter `x` pixels de 4 octets |
| `char *` | l'arithmétique se fait **en octets** ; avec un `int *`, `+ 1` avancerait de 4 |
| `*(unsigned int *)` | écrire les 4 octets du pixel d'un coup |
| test des bornes | un pixel hors image est ignoré au lieu d'écraser la mémoire voisine |

> [!warning] Ne jamais remplacer `line_len` par `w * 4`
> La MLX peut ajouter du padding en fin de ligne (alignement mémoire). Avec `w * 4`, l'image se décale d'une ligne à l'autre et devient penchée.

## Le format d'une couleur

`0x00RRGGBB` : un `int` où chaque octet est un canal. Le parser construit la couleur avec `rgb = (rgb << 8) | val` (voir [cours-parser/05](../cours-parser/05%20-%20P4%20Couleurs%20(automate).md)), ce qui donne exactement ce format. En little-endian, l'octet de B est rangé en premier en mémoire, et c'est ce qu'attend le serveur X.

## Pourquoi la fenêtre fait 960 × 720

Format 4:3, comme Wolfenstein 3D, et assez petit pour tenir sur les écrans de l'école. La fenêtre n'est pas redimensionnable (la MLX l'interdit), donc `WIN_W` et `WIN_H` sont des constantes de compilation.

## À retenir en 3 lignes

1. On dessine dans une image en mémoire, puis on l'affiche en une seule requête.
2. Adresse d'un pixel = `addr + y × line_len + x × bpp/8`, en arithmétique `char *`.
3. `line_len` vient de la MLX et s'utilise tel quel.

→ Suite : [03 - G2 Hooks et clavier](03%20-%20G2%20Hooks%20et%20clavier.md)
