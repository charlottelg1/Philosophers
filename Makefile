NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread  
RM = rm

INCLUDES = includes/philo.h

SRCS = main.c \
	check.c \
	init.c \
	utils.c \
	other.c \
	death.c \
	action.c \
	atoi.c \
	thread.c \

OBJS_DIR = objs/

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

$(OBJS_DIR)%.o: srcs/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	$(CC) $(CFLAGS) -I includes $(OBJS) -o $(NAME)

clean:
	$(RM) -rf $(OBJS_DIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

