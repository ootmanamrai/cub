CC = clang
CFLAGS = #-Wall -Werror -Wextra #-fsanitize=address -g3
RM = rm -f
FILES = lunchmap cub3d


OBJ = $(FILES:=.o)


NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
