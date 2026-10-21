#!/usr/bin/env bash
# run_tests.sh : lance cub3D sur maps/valid et maps/invalid
# Usage : bash tests/run_tests.sh [./cub3D]        (tests fonctionnels)
#         VG=1 bash tests/run_tests.sh [./cub3D]   (+ valgrind sur les invalides)
# Prerequis : make, bash tests/gen_maps.sh, une session graphique (DISPLAY)
BIN=${1:-./cub3D}
SUPP=tests/x11.supp
VGCMD=(valgrind -q --leak-check=full --show-leak-kinds=all
	--errors-for-leak-kinds=all --track-fds=yes --error-exitcode=42)
[ -f "$SUPP" ] && VGCMD+=(--suppressions="$SUPP")
G='\033[32m'; R='\033[31m'; Y='\033[33m'; N='\033[0m'
pass=0; fail=0

res() { # res OK|KO nom detail
	if [ "$1" = OK ]; then pass=$((pass + 1)); printf "${G}[OK]${N} %s\n" "$2"
	else fail=$((fail + 1)); printf "${R}[KO]${N} %s ${Y}%s${N}\n" "$2" "$3"; fi
}

expect_error() { # expect_error nom arg...
	local name=$1; shift
	local err code
	err=$(timeout 5 "$BIN" "$@" 2>&1 >/dev/null); code=$?
	if [ $code -eq 124 ]; then res KO "$name" "(ne s'arrete pas : fenetre ouverte ?)"
	elif [ $code -ge 128 ]; then res KO "$name" "(signal $((code - 128)) : crash)"
	elif [ $code -eq 0 ]; then res KO "$name" "(exit 0 sur une erreur)"
	elif [ "$(printf '%s\n' "$err" | head -n 1)" != "Error" ]; then
		res KO "$name" "(1re ligne de stderr != \"Error\")"
	else res OK "$name"; fi
	if [ "${VG:-0}" = 1 ]; then
		timeout 60 "${VGCMD[@]}" "$BIN" "$@" >/dev/null 2>/tmp/cub_vg.log
		if [ $? -eq 42 ]; then res KO "$name [valgrind]" "(voir /tmp/cub_vg.log)"
			cp /tmp/cub_vg.log "/tmp/cub_vg_$(basename "$name").log"
		else res OK "$name [valgrind]"; fi
	fi
}

expect_running() { # la fenetre doit rester ouverte 2 s (timeout => code 124)
	timeout 2 "$BIN" "$1" >/dev/null 2>&1
	local code=$?
	if [ $code -eq 124 ]; then res OK "$1"
	else res KO "$1" "(code $code : erreur ou crash sur une map valide)"; fi
}

[ -x "$BIN" ] || { echo "binaire $BIN introuvable (make ?)"; exit 2; }
[ -d maps/valid ] || { echo "lancer d'abord : bash tests/gen_maps.sh"; exit 2; }
[ "$(id -u)" = 0 ] && echo "attention : en root, les tests *noperm* ne sont pas fiables"

echo "=== Arguments"
expect_error "aucun argument"
expect_error "deux arguments" maps/valid/v_subject_small.cub maps/valid/v_min_3x3.cub
expect_error "fichier inexistant" maps/invalid/does_not_exist.cub
expect_error "argument vide" ""

echo "=== Scenes invalides"
for f in maps/invalid/* maps/invalid/.cub; do
	[ -e "$f" ] && expect_error "$f" "$f"
done

if [ -n "$DISPLAY" ]; then
	echo "=== Scenes valides (doivent rester ouvertes 2 s)"
	for f in maps/valid/*.cub; do expect_running "$f"; done
else
	echo "(pas de DISPLAY : scenes valides ignorees)"
fi

echo "=== Bilan : ${pass} OK, ${fail} KO"
[ $fail -eq 0 ]
