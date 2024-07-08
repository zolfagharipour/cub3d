NAME = cub3d
CC = cc
MLXFLAG	=	-lmlx -lXext -lX11 -g -lm
#CFLAGS = -Wall -Wextra -Werror -g -I include/
CFLAGS = -g -I include/

RM = rm -rf
# ***************************************************************************

SRCS = 	src/image_utils.c src/events.c src/image.c src/init_structs.c \
		src/main.c src/cleanup.c  src/minimap.c \
		src/caster.c src/line.c src/draw_walls.c src/move_player.c \
		src/error_checks.c src/read_from_file.c  src/texture.c \
		src/sprite.c src/math.c src/floor_ceiling.c src/door.c \
		src/ninja.c src/light.c src/draw_icon.c src/mouse.c src/caster_utils.c \
		src/shoot_ray.c

OBJDIR = ./obj
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean fclean re $(OBJDIR)

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@make --no-print-directory -C ./libft > /dev/null
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAG) ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\nFZ3D IS READY TO USE - use wisely\n\033[0m"

clean:
	@make --no-print-directory -C ./libft fclean > /dev/null
	@$(RM) $(OBJDIR) $(OBJS)
	@echo "\033[0;91mCleaning was successful\033[0m"

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)

re: fclean all


test : all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no ./$(NAME) bonus_map.txt