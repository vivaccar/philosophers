SRCS	=	philo.c utils.c input.c threads.c init.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

NAME	=	philo

CFLAGS  = 	-Wall -Wextra -Werror -g -fsanitize=thread	

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