NAME = cub3d
CC = cc
MLXFLAG = -g
//MLXFLAG	=	-lmlx -lXext -lX11 -g -lm
#CFLAGS = -Wall -Wextra -Werror -g -I include/
CFLAGS = -g -I include/

RM = rm -rf
# ***************************************************************************

SRCS = 	src/init_structs.c \
		src/main.c src/cleanup.c \
		src/error_checks.c src/read_from_file.c 

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
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no ./$(NAME) test_map.txt