#include "cub3d.h"

/*
** P4 - Couleurs : " 220, 100 ,0" -> 0x00DC6400. Aucune allocation.
**
** Automate lu une seule fois, de gauche a droite :
**   espaces* chiffres+ espaces* ',' espaces* chiffres+ espaces* ','
**   espaces* chiffres+ espaces* fin
**
** static int read_component(char *s, int *i, int *val)
**     sauter les espaces
**     val = 0 ; nb = 0
**     tant que s[*i] est un chiffre :
**         val = val * 10 + (s[*i] - '0') ; nb++ ; (*i)++
**         si val > 255 -> renvoyer 1        (pendant la lecture : pas d'overflow)
**     si nb == 0 -> renvoyer 1
**     sauter les espaces
**     renvoyer 0
**
** int parse_rgb(char *s, int *out)           0 = OK, 1 = erreur
**     i = 0 ; k = 0 ; rgb = 0
**     tant que k < 3 :
**         si read_component(s, &i, &val) -> renvoyer 1
**         rgb = (rgb << 8) | val
**         si k < 2 : si s[i] != ',' -> renvoyer 1 ; i++
**         k++
**     si s[i] != '\0' -> renvoyer 1          (rien apres le 3e nombre)
**     *out = rgb ; renvoyer 0
**
** Pas de ft_atoi (accepte '+', '-', deborde) ni de ft_split (fusionne les ',').
*/
