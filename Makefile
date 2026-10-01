NAME		:= cub3d
CC			:= cc 
CFLAGS		:= -Wall -Wextra -Werror -g3 -std=gnu17

MLXPATH		:= libs/mlx
MLXNAME		:= libmlx.a
MLX			:= $(MLXPATH)/$(MLXNAME)
LIBPATH		:= libs/libft
LIBNAME		:= libft.a
LIBFT		:= $(LIBPATH)/$(LIBNAME)

INCLUDE		:= -I includes -I $(MLXPATH) -I $(LIBPATH)/includes
LDFLAGS		:= -L $(MLXPATH) -lmlx -L $(LIBPATH) -lft -lXext -lX11 -lm -lz

SRCS		:= src/mandatory/main.c
OBJS		:= $(SRCS:.c=.o)


$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLXPATH)

$(LIBFT):
	$(MAKE) -C $(LIBPATH)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBPATH) clean
	-$(MAKE) -C $(MLXPATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBPATH) clean

re: fclean all

# bonus:

.PHONY: all clean fclean re