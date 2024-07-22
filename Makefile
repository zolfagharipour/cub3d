# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 13:31:28 by mzolfagh          #+#    #+#              #
#    Updated: 2024/07/22 13:31:29 by mzolfagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME2 = cub3D_bonus
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

SRCS2 = bonus/src/caster.c bonus/src/events.c bonus/src/image_utils.c \
		bonus/src/minimap.c bonus/src/cleanup.c bonus/src/file_parsing.c \
		bonus/src/init_structs.c bonus/src/move_player.c bonus/src/sprite.c \
		bonus/src/door.c bonus/src/file_parsing_utils.c bonus/src/line.c src/ninja.c \
		bonus/src/texture.c bonus/src/draw_walls.c bonus/src/fill_minimap.c \
		bonus/src/main.c bonus/src/read_colors.c bonus/src/floor_ceiling.c \
		bonus/src/map_parsing.c bonus/src/read_from_file.c bonus/src/error_checks.c \
		bonus/src/image.c bonus/src/math.c bonus/src/read_from_file_utils.c \
		bonus/src/validate_map.c bonus/src/caster_utils.c bonus/src/shoot_ray.c \
		bonus/src/mouse.c bonus/src/light.c bonus/src/draw_icon.c bonus/src/texture_open.c \
		bonus/src/move_player_utils.c bonus/src/cleanup_utils.c \
		bonus/src/init_structs_utils.c bonus/src/first_step_utils.c

OBJDIR = ./obj

OBJDIR2 = ./obj

OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

OBJS2 = $(patsubst bonus/src/%.c,$(OBJDIR)/%.o,$(SRCS2))

.PHONY: all clean fclean re $(OBJDIR)

all: $(OBJDIR) $(NAME)

bonus: $(OBJDIR) $(NAME2)

$(NAME): $(OBJS)
	@make --no-print-directory -C ./libft > /dev/null
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAG) ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\nFZ3D IS READY TO USE - use wisely\n\033[0m"

$(NAME2): $(OBJS2)
	@make --no-print-directory -C ./libft > /dev/null
	$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2) $(MLXFLAG) ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\nFZ3D IS READY TO USE - use wisely\n\033[0m"

clean:
	@make --no-print-directory -C ./libft fclean > /dev/null
	@$(RM) $(OBJDIR) $(OBJS)
	@echo "\033[0;91mCleaning was successful\033[0m"

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR2)/%.o: bonus/src/%.c
	@mkdir -p $(OBJDIR2)
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME) $(NAME2)

re: fclean all


test : all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no ./$(NAME) bonus_map.txt