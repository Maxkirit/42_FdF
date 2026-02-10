CC = gcc
FLAGS = -Wall -Werror -Wextra -g
NAME = fdf
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
LIBDIR = libft
MLXDIR = mlx_linux
SRC = color_utils.c \
	color_utils2.c \
	fdf.c \
	utils.c \
	utils2.c \
	utils3.c \
	get_map.c \
	mlx_utils.c \
	set_pts.c \
	rotation.c \
	draw_img.c

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	make -C $(MLXDIR)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

$(LIBFT):
	make -C $(LIBDIR)

clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re