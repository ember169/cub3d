#include "cub3d.h"

/*
** P2 - Dispatch des elements (NO SO WE EA F C)
**
** found = masque de bits : bit n = element n vu (ordre de t_elem)
**   doublon : found & (1 << el)      tout present : found == ALL_ELEMS
**
** static int elem_id(char *mot, int len)
**     len == 2 ET mot commence par "NO"  -> EL_NO
**     len == 2 ET mot commence par "SO"  -> EL_SO
**     len == 2 ET mot commence par "WE"  -> EL_WE
**     len == 2 ET mot commence par "EA"  -> EL_EA
**     len == 1 ET mot[0] == 'F'          -> EL_F
**     len == 1 ET mot[0] == 'C'          -> EL_C
**     sinon                              -> -1
**     (longueur ET contenu : "NOX" et "NO." sont refuses)
**
** char *parse_element(t_game *g, char *line)      NULL ou message E_*
**     si line contient '\t' ou '\r'               -> E_BADSPACE
**     i = nombre d'espaces de tete
**     len = longueur du mot qui commence en i (jusqu'a ' ' ou '\0')
**     el = elem_id(line + i, len)
**     si el == -1 :
**         si line[i] est '0' ou '1'               -> E_MISSING  (map trop tot)
**         sinon                                   -> E_IDENT
**     si g->sc.found & (1 << el)                  -> E_DUP
**     reste = line + i + len
**     si el <= EL_EA :
**         msg = parse_texture(g, el, reste)       (P3)
**         si msg -> renvoyer msg
**     sinon :
**         si parse_rgb(reste, &couleur) != 0      (P4)  -> E_COLOR
**         si el == EL_F : g->sc.floor = couleur
**         sinon         : g->sc.ceil  = couleur
**     g->sc.found |= 1 << el
**     renvoyer NULL
*/
