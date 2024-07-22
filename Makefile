NAME = cub3d
CC = cc
MLXFLAG	= -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Wextra -Werror -g -I include/

RM = rm -rf
# ***************************************************************************

SRCS = 	src/caster.c src/events.c src/image_utils.c src/minimap.c \
		src/cleanup.c src/file_parsing.c src/init_structs.c \
		src/move_player.c src/sprite.c src/door.c src/file_parsing_utils.c \
		src/line.c src/ninja.c src/texture.c src/draw_walls.c \
		src/fill_minimap.c src/main.c src/read_colors.c \
		src/floor_ceiling.c src/map_parsing.c src/read_from_file.c \
		src/error_checks.c src/image.c src/math.c \
		src/read_from_file_utils.c src/validate_map.c src/caster_utils.c \
		src/shoot_ray.c src/mouse.c src/light.c src/draw_icon.c src/texture_open.c \
		src/move_player_utils.c src/cleanup_utils.c src/init_structs_utils.c \
		src/first_step_utils.c


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