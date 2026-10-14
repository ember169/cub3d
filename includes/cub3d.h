#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "mlx.h"

/* Choix techniques */
# define WIN_W 960
# define WIN_H 720
# define WIN_TITLE "cub3D"
# define FOV_PLANE 0.66
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.5
# define MAX_DT 0.05
# define MIN_PERP 0.0001

/* Bitmask des 6 elements du .cub (bit n = element n de t_elem) */
# define ALL_ELEMS 63

/* Messages d'erreur : exit_game() ecrit "Error\n" puis le message */
# define E_USAGE "usage: ./cub3D <scene.cub>"
# define E_EXT "scene file must end with .cub"
# define E_OPEN "cannot open scene file"
# define E_ISDIR "path is a directory"
# define E_MALLOC "memory allocation failed"
# define E_EMPTY "scene file is empty"
# define E_IDENT "unknown or misplaced identifier"
# define E_DUP "element defined twice"
# define E_MISSING "missing element before map"
# define E_TEXPATH "invalid texture path"
# define E_TEXLOAD "texture could not be loaded"
# define E_COLOR "invalid color (expected R,G,B in [0,255])"
# define E_NOMAP "no map in scene file"
# define E_MAPCHAR "invalid character in map"
# define E_MAPGAP "empty line inside map or content after map"
# define E_PLAYER "map must contain exactly one player"
# define E_OPENMAP "map is not closed by walls"
# define E_BADSPACE "tab or carriage return in scene file (CRLF?)"
# define E_MLX "minilibx initialisation failed"

typedef enum e_elem
{
	EL_NO,
	EL_SO,
	EL_WE,
	EL_EA,
	EL_F,
	EL_C
}	t_elem;

typedef enum e_key
{
	K_W,
	K_A,
	K_S,
	K_D,
	K_LEFT,
	K_RIGHT,
	K_COUNT
}	t_key;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

/* Resultat du parsing (lines = fichier brut, libere apres parsing) */
typedef struct s_scene
{
	char	*tex_path[4];
	int		floor;
	int		ceil;
	int		found;
	char	**lines;
}	t_scene;

/* grid rectangulaire h x w, completee par des espaces */
typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
}	t_map;

/* Repere : x = colonne (vers l'Est), y = ligne (vers le Sud) */
typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	side;
	t_vec	delta;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit_side;
	double	perp;
}	t_ray;

typedef struct s_col
{
	int		x;
	int		line_h;
	int		start;
	int		end;
	int		tex_x;
	double	step;
	double	tex_pos;
	t_img	*tex;
}	t_col;

/* zbuf, ext et ext_free restent NULL en mandatory (crochets bonus) */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		tex[4];
	t_scene		sc;
	t_map		map;
	t_player	pl;
	int			keys[K_COUNT];
	double		last_time;
	double		*zbuf;
	void		*ext;
	void		(*ext_free)(struct s_game *g);
}	t_game;

/* E - sortie et memoire */
void	exit_game(t_game *g, int status, char *msg);
void	free_tab(char **tab);
void	free_scene(t_scene *sc);
void	destroy_gfx(t_game *g);

/* P - parsing : un char * renvoye = message E_* (NULL = OK), jamais alloue */
void	parse_scene(t_game *g, char *path);
int		check_extension(char *path, char *ext);
int		check_readable_file(char *path);
char	**read_lines(char *path, int *err);
int		is_blank(char *line);
char	*parse_element(t_game *g, char *line);
char	*parse_texture(t_game *g, int el, char *rest);
int		parse_rgb(char *str, int *out);
char	*build_map(t_game *g, char **lines);
char	*check_chars(t_map *map);
int		check_map(t_map *map, int *err_row, int *err_col);
void	init_player(t_game *g);

/* Points de variation (fichier mandatory OU _bonus, meme prototype) */
int		is_map_char(char c);
int		is_walkable(char c);
int		is_solid(t_game *g, int x, int y);
t_img	*select_texture(t_game *g, t_ray *r);

/* G - MiniLibX */
void	gfx_init(t_game *g);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_texel(t_img *tex, int x, int y);
void	setup_hooks(t_game *g);
int		on_key_press(int keysym, t_game *g);
int		on_key_release(int keysym, t_game *g);
int		on_close(t_game *g);
int		on_focus_out(t_game *g);
int		game_loop(t_game *g);

/* R - raycasting et rendu */
void	render_frame(t_game *g);
void	cast_ray(t_game *g, int x, t_ray *r);
void	run_dda(t_game *g, t_ray *r);
void	draw_column(t_game *g, t_ray *r, int x);

/* M - deplacements */
double	now_seconds(void);
void	update_player(t_game *g, double dt);
void	rotate_player(t_player *p, double angle);
void	try_move(t_game *g, double dx, double dy);

#endif