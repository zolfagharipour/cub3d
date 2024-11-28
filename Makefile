# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzolfagh <mzolfagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 13:31:28 by mzolfagh          #+#    #+#              #
#    Updated: 2024/07/23 15:11:05 by mzolfagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME2 = cub3D_bonus
CC = cc
MLXFLAG	= -lmlx -lXext -lX11 -lm
CFLAGS = -Wall -Wextra -Werror -g -I include/

RM = rm -rf

# ***************************************************************************

SRCS = 	src/caster.c src/events.c src/image_utils.c \
		src/cleanup.c src/file_parsing.c src/init_structs.c \
		src/move_player.c src/file_parsing_utils.c \
		src/texture.c src/draw_walls.c \
		src/fill_minimap.c src/main.c src/read_colors.c \
		src/floor_ceiling.c src/map_parsing.c src/read_from_file.c \
		src/error_checks.c src/image.c src/math.c \
		src/read_from_file_utils.c src/validate_map.c src/caster_utils.c \
		src/shoot_ray.c src/light.c src/texture_open.c \
		src/move_player_utils.c src/cleanup_utils.c src/init_structs_utils.c \
		src/first_step_utils.c

SRCS2 = bonus/src/bonus_caster.c bonus/src/bonus_events.c bonus/src/bonus_image_utils.c \
		bonus/src/bonus_minimap.c bonus/src/bonus_cleanup.c bonus/src/bonus_file_parsing.c \
		bonus/src/bonus_init_structs.c bonus/src/bonus_move_player.c bonus/src/bonus_sprite.c \
		bonus/src/bonus_door.c bonus/src/bonus_file_parsing_utils.c bonus/src/bonus_line.c \
		bonus/src/bonus_ninja.c bonus/src/bonus_texture.c bonus/src/bonus_draw_walls.c bonus/src/bonus_fill_minimap.c \
		bonus/src/bonus_main.c bonus/src/bonus_read_colors.c bonus/src/bonus_floor_ceiling.c \
		bonus/src/bonus_map_parsing.c bonus/src/bonus_read_from_file.c bonus/src/bonus_error_checks.c \
		bonus/src/bonus_image.c bonus/src/bonus_math.c bonus/src/bonus_read_from_file_utils.c \
		bonus/src/bonus_validate_map.c bonus/src/bonus_caster_utils.c bonus/src/bonus_shoot_ray.c \
		bonus/src/bonus_mouse.c bonus/src/bonus_light.c bonus/src/bonus_draw_icon.c bonus/src/bonus_texture_open.c \
		bonus/src/bonus_move_player_utils.c bonus/src/bonus_cleanup_utils.c \
		bonus/src/bonus_init_structs_utils.c bonus/src/bonus_first_step_utils.c

OBJDIR = ./obj

OBJDIR2 = ./obj_bonus

OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

OBJS2 = $(patsubst bonus/src/%.c,$(OBJDIR2)/%.o,$(SRCS2))

.PHONY: all clean fclean re bonus $(OBJDIR) $(OBJDIR2)

all: $(OBJDIR) $(NAME)

bonus: $(OBJDIR2) $(NAME2)

$(NAME): $(OBJS)
	@make --no-print-directory -C ./libft > /dev/null
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLXFLAG) ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\nFZ3D IS READY TO USE - use wisely\n\033[0m"

$(NAME2): $(OBJS2)
	@make --no-print-directory -C ./libft > /dev/null
	$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2) $(MLXFLAG) ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\nFZ3D PRO IS READY TO USE - use wisely\n\033[0m"

clean:
	@make --no-print-directory -C ./libft fclean > /dev/null
	@$(RM) $(OBJDIR) $(OBJS) $(OBJDIR2) $(OBJS2)
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

bonusre: fclean bonus
