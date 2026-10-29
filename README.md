*This project has been created as part of the 42 curriculum by achavier, lgervet.*

# cub3D

## Description

cub3D is a small first-person 3D engine written in C with the MiniLibX, inspired by
Wolfenstein 3D (id Software, 1992). It reads a `.cub` scene file (wall textures,
floor and ceiling colors, and a 2D grid map), validates it, and renders the maze in
real time using **ray casting**: one ray per screen column is traced through the grid
with the DDA algorithm, and the distance to the first wall gives the height of the
textured wall slice drawn in that column.

Main features:
- strict `.cub` parser with explicit error messages (`Error\n<message>` on stderr);
- textured walls (a different texture for each facing direction), floor/ceiling colors;
- smooth, frame-rate independent movement (delta time), held keys, window focus handling;
- clean exit on ESC and on the window close button, no memory leaks.

## Instructions

### Requirements
Linux with an X11 server (XWayland works), `cc`, `make`, and the X11 development headers:

```bash
sudo dnf install gcc make libX11-devel libXext-devel      # Fedora
sudo apt install gcc make libx11-dev libxext-dev          # Debian/Ubuntu
```

The MiniLibX sources are included in `libs/mlx/` and built by the Makefile. The
project does not link on macOS (no `Xext`).

### Build
```bash
make          # builds ./cub3D
make clean | make fclean | make re
```

### Run
```bash
./cub3D maps/demo/demo.cub
```
Run the program from the repository root: texture paths in `.cub` files are relative
to the current directory. More valid scenes are generated in `maps/valid/` by
`bash tests/gen_maps.sh`.

### Controls
| Key | Action |
|---|---|
| W / S | move forward / backward |
| A / D | strafe left / right |
| ← / → | turn left / right |
| ESC or window close button | quit |

### Scene file (`.cub`)
A file has two zones, in this order: the **elements** zone, then the **map**.

```text
NO ./textures/wall_n.xpm
SO ./textures/wall_s.xpm
WE ./textures/wall_w.xpm
EA ./textures/wall_e.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```
- The six elements (`NO SO WE EA F C`) may come in any order and be separated by
  empty lines. Each must appear exactly once.
- The map is always last. Map characters: `0` floor, `1` wall, `N`/`S`/`E`/`W` player
  spawn and orientation (exactly one), space = void.

## How the parser works

All data lives in one `t_game g` structure ([includes/cub3d.h](includes/cub3d.h)),
zeroed at the start of `main`. Every pointer is therefore `NULL` until something is
allocated, which makes `exit_game` safe to call from anywhere.

### Single exit point: `exit_game(g, status, msg)`
Defined in `src/core/exit/`. If `msg` is not `NULL`, it prints `Error\n<msg>\n` on
stderr. It then frees everything that exists (scene paths, raw lines, map grid,
textures, frame, window, MLX display) and calls `exit(status)`. Each freed pointer is
set back to `NULL`, so it works whether 0 or 100 things were allocated.

### Error convention
- "Leaf" functions never exit. They return either an `int` (0 = OK) or a `char *`
  that is `NULL` on success and otherwise **the `E_*` message itself** (a string
  literal, never allocated, nothing to free).
- Only "orchestrator" functions (`main`, `parse_scene`, hooks) call `exit_game`:
  `if (msg) exit_game(g, 1, msg);`.

### Pipeline
```text
parse_scene(g, path)
 ├─ check_extension        must end with ".cub"                      E_EXT
 ├─ check_readable_file    directory? cannot open?                   E_ISDIR / E_OPEN
 ├─ read_lines             whole file -> g->sc.lines                 E_MALLOC / E_EMPTY   (P1)
 ├─ elements zone          parse_element on each non-blank line      (P2)
 │    ├─ parse_texture     NO/SO/WE/EA                               (P3)
 │    └─ parse_rgb         F/C                                       (P4)
 ├─ build_map              remaining lines -> rectangular grid       (P5)
 ├─ check_chars            valid characters, exactly one player      (P6)
 ├─ check_map              map closed by walls                       (P7)
 ├─ init_player            position + direction + camera plane       (P8)
 └─ free raw lines         the raw file is no longer needed
```

### Why the whole file is read first (P1)
The rule "no empty line *inside* the map, but empty lines *after* it are fine" can only
be judged by knowing what follows. `read_lines` therefore loads every line (without the
trailing `\n`, empty lines kept) into a `NULL`-terminated array, reading until
`get_next_line` returns `NULL` so its static buffer is always emptied.
Directories are detected with `open(path, O_RDONLY | O_DIRECTORY)` (no `stat`).
Extension check compares the **end** of the base name, so `.cub`, `a.cub.txt` and
`a.CUB` are rejected.

### The elements zone: the `found` bitmask (P2)
`g->sc.found` is an integer where bit *n* means "element *n* has been seen"
(order of `t_elem`):

```text
bit      5  4  3   2   1   0
element  C  F  EA  WE  SO  NO
```
- Duplicate: `found & (1 << el)`.
- All present: `found == ALL_ELEMS` (63 = `0b111111`).
- The zone ends exactly when the mask is complete; the next non-blank line is the
  start of the map. Elements are never searched for after that point.

`parse_element(g, line)`:
1. reject `\t` and `\r` (`E_BADSPACE`);
2. skip leading spaces, isolate the first word;
3. `elem_id` matches the word by length **and** content (`NOX` and `NO./a.xpm` are
   refused); unknown word: `E_MISSING` if the line starts with `0`/`1` (map too
   early), else `E_IDENT`;
4. already seen: `E_DUP`;
5. `NO/SO/WE/EA` go to `parse_texture`, `F/C` go to `parse_rgb` (`E_COLOR`);
6. set the bit and return `NULL`.

## Testing

```bash
bash tests/gen_maps.sh          # generates maps/valid, maps/invalid, textures/test
bash tests/run_tests.sh         # every invalid map must print "Error"
VG=1 bash tests/run_tests.sh    # same under valgrind (leaks and file descriptors)
```
Unit tests live in `tests/unit/`:
- `t_file.c` prints `[line]` for each line read by `read_lines`, so empty lines (`[]`)
  and the absence of trailing `\n` are visible.
- Functions that are not written yet are replaced by **stubs** (fake minimal
  versions that always succeed) kept in `tests/unit/`, never in `src/`, so a unit can
  be tested alone and the real function never clashes with its stub.

Check leaks and file descriptors with:
```bash
valgrind --leak-check=full --track-fds=yes ./cub3D maps/demo/demo.cub
```

## Technical choices

- **Camera as two vectors** (`dir`, `plane`) instead of an angle; `|plane| = 0.66`
  gives a ~66° field of view matching the 4:3 window (960×720).
- **No fisheye**: the perpendicular distance to the camera plane is used.
- **Texture convention**: the `NO` texture is the one seen when looking north.
- **Movement** uses delta time (`gettimeofday`) capped at 50 ms, so speed is the
  same on every machine and the player can never skip over a wall. Diagonal
  movement is normalized (W+D is not faster than W).
- **Minimal collision**: the player position cannot enter a wall cell, tested axis by
  axis so the player slides along walls (prevents leaving the map).
- **Parser choices** where the subject is silent: leading and trailing spaces around
  elements accepted; tabs and CR (CRLF files) rejected; a "blank" line is empty or
  only spaces; floor and ceiling may be equal; empty lines after the map accepted,
  inside the map rejected.
- **Build**: `-std=gnu17`, because GCC ≥ 15 defaults to C23, where the MiniLibX hook
  prototype `int (*)()` means "no parameters".

## Resources

- Lode Vandevenne, *Raycasting* tutorial: https://lodev.org/cgtutor/raycasting.html
- `man 2 open`, `man 3 exit`; Valgrind and GDB manuals.
- MiniLibX man pages and sources.
- Textures: the four wall textures (`textures/wall_*.xpm`, 64×64 bricks) are original
  work by the authors, drawn with ImageMagick. Test textures in `textures/test/` are
  generated by `tests/gen_maps.sh`. Details in `textures/CREDITS.md`.

### AI usage

AI tools were used throughout the project.

- **Planning and learning**: the project roadmap (units, pseudo-code, pitfalls,
  milestones) was written with Claude and used as our course material on ray casting,
  DDA, the MiniLibX and the game loop.
- **Tests**: the test map generator `tests/gen_maps.sh` and the test runner
  `tests/run_tests.sh` come from that roadmap (AI-generated).
- **Code (achavier)**: Claude Code wrote most of the graphics and rendering code
  (`src/core/gfx/`, `src/core/render/`, `src/mandatory/hooks.c`, `loop.c`, `main.c`),
  the movement and collision code (`src/core/move/`, `src/mandatory/collide.c`), the
  Makefile fixes and the Norm fixes (42 headers, spacing), under our direction:
  unit by unit, one git branch per unit, each diff reviewed before every commit,
  tested by hand and with the test suite.
- **Debugging and checks**: Claude Code ran builds, tests, valgrind and norminette
  and explained the causes of the bugs found.
- **Code and docs (lgervet)**: according to the git history, Claude Code co-wrote
  the fix of `exit_game` and the first parsing step (file reading and scene loading:
  `src/core/exit/`, `src/core/parsing/file.c`, `parse_scene.c`), the normalization of
  all files to LF line endings (`.gitattributes`), and the engine course
  `docs/cours-moteur/` used to prepare the defense. The rest of the parser
  (`src/core/parsing/`: elements, colors, map building and checks, player) and the
  parser course `docs/cours-parser/` were committed without an AI co-author.
  This statement is based only on the co-author trailers recorded in the git history;
  it does not say whether AI was used for the commits without such a trailer.
