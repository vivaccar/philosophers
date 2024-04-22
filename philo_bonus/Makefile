SRCS	=	main_bonus.c input_bonus.c utils_bonus.c utils_bonus2.c  processes_bonus.c init_bonus.c eating_bonus.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

NAME	=	philo_bonus

CFLAGS  = 	-Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# -g -fsanitize=thread
# -g -fsanitize=address