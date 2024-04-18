SRCS	=	philo_bonus.c input_bonus.c utils_bonus.c

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

# -fsanitize=thread
# -fsanitize=address