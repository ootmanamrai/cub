CC = cc
CFLAGS = #-Wall -Werror -Wextra #-fsanitize=address -g3
RM = rm -f
FILES = lunchmap.c cub3d.c
OBJ = $(FILES:.c=.o)
NAME = cub3d

all: $(NAME)

UNAME = $(shell uname)
ifeq ($(UNAME),Linux)
    MLX_FLAGS = -lmlx -lXext -lX11 -lm
endif
ifeq ($(UNAME),Darwin)
    MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
endif


$(NAME): $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(MLX_FLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
