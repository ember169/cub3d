NAME		:= cub3D
CC			:= cc 
CFLAGS		:= -Wall -Wextra -Werror -g3 -std=gnu17

MLXPATH		:= libs/mlx
MLXNAME		:= libmlx.a
MLX			:= $(MLXPATH)/$(MLXNAME)
LIBPATH		:= libs/libft
LIBNAME		:= libft.a
LIBFT		:= $(LIBPATH)/$(LIBNAME)

INCLUDES	:= -I includes -I $(MLXPATH) -I $(LIBPATH)/includes
LDFLAGS		:= -L $(MLXPATH) -lmlx -L $(LIBPATH) -lft -lXext -lX11 -lm -lz

SRCS		:= src/mandatory/main.c \
			   src/core/gfx/gfx_init.c \
			   src/core/gfx/pixel.c \
			   src/core/gfx/keys.c \
			   src/mandatory/hooks.c \
			   src/mandatory/loop.c
OBJS		:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLXPATH) -f Makefile.mk INC=/usr/include CFLAGS="-O3 -std=gnu17 -I/usr/include"

$(LIBFT):
	$(MAKE) -C $(LIBPATH)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBPATH) clean
	-$(MAKE) -C $(MLXPATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBPATH) fclean

re: fclean all

# bonus:

.PHONY: all clean fclean re