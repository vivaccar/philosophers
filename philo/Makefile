SRCS	=	main.c init.c utils.c utils2.c input.c threads.c one_philo.c eating.c 

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

NAME	=	philo

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