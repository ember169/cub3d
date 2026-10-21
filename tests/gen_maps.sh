#!/usr/bin/env bash
# gen_maps.sh : genere maps/valid, maps/invalid et textures/test
# Usage (depuis la racine du repo) : bash tests/gen_maps.sh
# Convention de nommage : v_* = doit se lancer, i_* = doit afficher "Error"
#                         *_choice_* = depend d'un choix documente (cf. roadmap)
set -e
V=maps/valid
I=maps/invalid
T=textures/test
chmod -R u+rwx maps "$T" 2>/dev/null || true
rm -rf maps "$T"
mkdir -p "$V" "$I" "$T"

# ---------- textures de test : 64x64, barre a gauche + bloc en haut a gauche
# (si la barre apparait a droite a l'ecran => texture inversee)
xpm() {
	awk -v n="$1" -v bg="$2" -v fg="$3" 'BEGIN {
		printf "/* XPM */\nstatic char *%s[] = {\n\"64 64 2 1\",\n", n;
		printf "\". c %s\",\n\"# c %s\",\n", bg, fg;
		for (y = 0; y < 64; y++) {
			l = "";
			for (x = 0; x < 64; x++)
				l = l ((x < 8 || (y < 8 && x < 32)) ? "#" : ".");
			printf "\"%s\"%s\n", l, (y < 63) ? "," : "";
		}
		print "};";
	}' > "$T/$1.xpm"
}
xpm no "#1D3557" "#F1FAEE"
xpm so "#6A040F" "#FFBA08"
xpm we "#2D6A4F" "#D8F3DC"
xpm ea "#5A189A" "#E0AAFF"
printf 'this is not an xpm\n' > "$T/corrupt.xpm"
: > "$T/empty.xpm"
mkdir -p "$T/dir.xpm"
cp "$T/no.xpm" "$T/north.png"
cp "$T/no.xpm" "$T/noperm.xpm" && chmod 000 "$T/noperm.xpm"

NO="NO ./$T/no.xpm"
SO="SO ./$T/so.xpm"
WE="WE ./$T/we.xpm"
EA="EA ./$T/ea.xpm"
F="F 220,100,0"
C="C 225,30,0"
hdr() { printf '%s\n%s\n%s\n%s\n\n%s\n%s\n\n' "$NO" "$SO" "$WE" "$EA" "$F" "$C"; }
MAP='111111
100101
101001
1100N1
111111'
# ok NAME : ecrit stdin dans maps/valid ; ko NAME : dans maps/invalid
ok() { cat > "$V/$1.cub"; }
ko() { cat > "$I/$1.cub"; }
# kc NAME "ligne F" "ligne C" : cas d'erreur sur les couleurs
kc() { printf '%s\n%s\n%s\n%s\n%s\n%s\n\n%s\n' "$NO" "$SO" "$WE" "$EA" \
	"$2" "$3" "$MAP" | ko "$1"; }

# ======================= VALIDES =======================
{ hdr; echo "$MAP"; } | ok v_subject_small
{ hdr; cat <<'M'; } | ok v_subject_big
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
M
for d in N S E W; do
	{ hdr; printf '11111\n10001\n10%s01\n10001\n11111\n' "$d"; } | ok "v_facing_$d"
done
{ hdr; printf '111\n1N1\n111\n'; } | ok v_min_3x3
{ printf '%s\n\n\n%s\n%s\n\n%s\n\n\n%s\n%s\n\n\n%s\n' "$C" "$EA" "$NO" "$F" "$WE" \
	"$SO" "$MAP"; } | ok v_order_and_empty_lines
{ printf 'NO      ./%s/no.xpm   \nSO ./%s/so.xpm\nWE  ./%s/we.xpm\n' "$T" "$T" "$T";
	printf 'EA ./%s/ea.xpm\nF    220,100,0\nC 225,30,0   \n\n%s\n' "$T" "$MAP"; } \
	| ok v_extra_spaces_elements
{ hdr | sed 's/^/   /'; echo "$MAP"; } | ok v_choice_leading_spaces_elements
{ hdr; echo "$MAP"; printf '\n\n\n'; } | ok v_trailing_empty_lines
{ hdr; printf '%s' "$MAP"; } | ok v_no_final_newline
{ hdr; printf '111111   \n100101  \n101001\n1100N1 \n111111    \n'; } \
	| ok v_trailing_spaces_in_map
{ printf '%s\n%s\n%s\n%s\nF 000,010,255\nC 0,0,0\n\n%s\n' "$NO" "$SO" "$WE" "$EA" \
	"$MAP"; } | ok v_leading_zeros_and_black
{ printf '%s\n%s\n%s\n%s\nF 50,50,50\nC 50,50,50\n\n%s\n' "$NO" "$SO" "$WE" "$EA" \
	"$MAP"; } | ok v_same_floor_ceiling
{ hdr; cat <<'M'; } | ok v_inner_void
1111111
1000001
1011101
101 101
1011101
100N001
1111111
M
{ hdr; cat <<'M'; } | ok v_two_islands
1111  11111
1N01  10001
1111  11111
M
{ hdr; cat <<'M'; } | ok v_long_corridor
1111111111111111111111111111111111111111111111111111111111111
1E00000000000000000000000000000000000000000000000000000000001
1111111111111111111111111111111111111111111111111111111111111
M
{ hdr; awk 'BEGIN { w = 120; h = 80;
	for (y = 0; y < h; y++) { l = "";
		for (x = 0; x < w; x++) {
			c = "0";
			if (x == 0 || y == 0 || x == w - 1 || y == h - 1) c = "1";
			else if (x % 6 == 0 && y % 6 == 0) c = "1";
			if (x == 3 && y == 3) c = "S";
			l = l c; }
		print l; } }'; } | ok v_big_120x80
{ printf '%s\n%s\n%s\n%s\nF 220, 100, 0\nC 225 ,30 , 0\n\n%s\n' "$NO" "$SO" "$WE" \
	"$EA" "$MAP"; } | ok v_choice_spaces_around_commas

# ===================== INVALIDES : fichier =====================
{ hdr; echo "$MAP"; } > "$I/i_noext"
{ hdr; echo "$MAP"; } > "$I/i_ext.cu"
{ hdr; echo "$MAP"; } > "$I/i_ext.cubb"
{ hdr; echo "$MAP"; } > "$I/i_ext.CUB"
{ hdr; echo "$MAP"; } > "$I/.cub"
mkdir -p "$I/i_directory.cub"
{ hdr; echo "$MAP"; } | ko i_noperm && chmod 000 "$I/i_noperm.cub"
: | ko i_empty
printf '\n\n\n' | ko i_only_newlines
printf '   \n  \n' | ko i_only_spaces
{ hdr; echo "$MAP"; } | sed 's/$/\r/' | ko i_choice_crlf

# ===================== INVALIDES : elements =====================
{ printf '%s\n%s\n%s\n%s\n%s\n\n%s\n' "$SO" "$WE" "$EA" "$F" "$C" "$MAP"; } | ko i_missing_NO
{ printf '%s\n%s\n%s\n%s\n%s\n\n%s\n' "$NO" "$SO" "$WE" "$EA" "$F" "$MAP"; } | ko i_missing_C
{ printf '%s\n' "$NO"; hdr; echo "$MAP"; } | ko i_duplicate_NO
{ printf '%s\n' "$F"; hdr; echo "$MAP"; } | ko i_duplicate_F
{ printf 'XX ./%s/no.xpm\n' "$T"; hdr; echo "$MAP"; } | ko i_unknown_identifier
{ hdr | sed 's/^NO /no /'; echo "$MAP"; } | ko i_lowercase_identifier
{ hdr | sed 's/^NO /NO/'; echo "$MAP"; } | ko i_identifier_glued_to_path
{ hdr | sed 's/^NO .*/NO/'; echo "$MAP"; } | ko i_texture_no_path
{ hdr | sed "s|^NO .*|NO ./$T/no.xpm ./$T/so.xpm|"; echo "$MAP"; } | ko i_texture_two_paths
{ hdr | sed "s|^NO .*|NO ./$T/nope.xpm|"; echo "$MAP"; } | ko i_texture_not_found
{ hdr | sed "s|^NO .*|NO ./$T/dir.xpm|"; echo "$MAP"; } | ko i_texture_is_directory
{ hdr | sed "s|^NO .*|NO ./$T/north.png|"; echo "$MAP"; } | ko i_texture_bad_extension
{ hdr | sed "s|^NO .*|NO ./$T/corrupt.xpm|"; echo "$MAP"; } | ko i_texture_corrupted
{ hdr | sed "s|^NO .*|NO ./$T/empty.xpm|"; echo "$MAP"; } | ko i_texture_empty_file
{ hdr | sed "s|^NO .*|NO ./$T/noperm.xpm|"; echo "$MAP"; } | ko i_texture_no_permission
{ echo "$MAP"; echo; hdr; } | ko i_map_before_elements
{ printf '%s\n%s\n%s\n\n%s\n%s\n%s\n%s\n' "$NO" "$SO" "$WE" "$MAP" "$EA" "$F" "$C"; } \
	| ko i_map_between_elements
{ hdr; echo "$MAP"; echo; echo "$F"; } | ko i_element_after_map
{ hdr | sed 's/^NO /NO\t/'; echo "$MAP"; } | ko i_choice_tab_separator

# ===================== INVALIDES : couleurs =====================
kc i_color_two_values "F 220,100" "$C"
kc i_color_four_values "F 220,100,0,5" "$C"
kc i_color_over_255 "F 256,100,0" "$C"
kc i_color_negative "$F" "C -1,30,0"
kc i_color_letters "F 22a,100,0" "$C"
kc i_color_empty_component "F 220,,0" "$C"
kc i_color_trailing_comma "F 220,100,0," "$C"
kc i_color_leading_comma "F ,220,100,0" "$C"
kc i_color_overflow "F 99999999999999999999,0,0" "$C"
kc i_color_space_in_number "F 2 20,100,0" "$C"
kc i_color_no_value "F" "$C"
kc i_color_plus_sign "F +10,100,0" "$C"
kc i_color_hex "F 0xFF,0,0" "$C"
kc i_color_float "F 1.5,0,0" "$C"
kc i_color_only_commas "F ,," "$C"

# ===================== INVALIDES : map =====================
hdr | ko i_no_map
{ hdr; printf '11111\n10001\n11111\n'; } | ko i_no_player
{ hdr; printf '111111\n1N0001\n1000S1\n111111\n'; } | ko i_two_players
{ hdr; printf '111111\n1N0201\n111111\n'; } | ko i_invalid_char_2
{ hdr; printf '111111\n1N0\t01\n111111\n'; } | ko i_tab_in_map
{ hdr; printf '111011\n1N0001\n111111\n'; } | ko i_open_top
{ hdr; printf '111111\n1N0001\n110111\n'; } | ko i_open_bottom
{ hdr; printf '111111\n0N0001\n111111\n'; } | ko i_open_left
{ hdr; printf '111111\n1N0000\n111111\n'; } | ko i_open_right
{ hdr; printf '111111\n100001\n10 001\n1N0001\n111111\n'; } | ko i_hole_inside
{ hdr; printf '11N111\n100001\n111111\n'; } | ko i_player_on_edge
{ hdr; printf '111111\n1N0001\n1 1111\n111111\n'; } | ko i_player_next_to_space
{ hdr; printf '1111\n100001\n1N0001\n111111\n'; } | ko i_irregular_open
{ hdr; printf '111111\n100001\n\n100N01\n111111\n'; } | ko i_empty_line_inside_map
{ hdr; printf '111111\n100001\n   \n100N01\n111111\n'; } | ko i_spaces_line_inside_map
{ hdr; echo "$MAP"; printf '\n1111\n'; } | ko i_content_after_map
{ hdr; printf '1N1\n'; } | ko i_single_row
{ hdr; printf '1111\n1001\n1111\n\n11111\n1N001\n11111\n'; } | ko i_two_maps

echo "valid   : $(ls "$V" | wc -l) fichiers"
echo "invalid : $(ls -A "$I" | wc -l) entrees (+ cas sans fichier dans run_tests.sh)"
