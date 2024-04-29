SRCS	=	main.c init.c utils.c utils2.c input.c threads.c one_philo.c eating.c handle_errors.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

NAME	=	philo

CFLAGS  = 	-Wall -Wextra -Werror -g -fsanitize=address
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# -g -fsanitize=thread
