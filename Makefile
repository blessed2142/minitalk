NAME	= server

NAME2	= client

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

SRCS	= server.c
SRCS2	= client.c

OBJS	= $(SRCS:.c=.o)
OBJS2	= $(SRCS2:.c=.o)

all: $(NAME2) $(NAME) 
%.o: 	%.c 
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) 
			$(CC) $(OBJS) -o ${NAME}

$(NAME2):	$(OBJS2)
			$(CC) $(OBJS2) -o ${NAME2}

clean:
	-rm -rf $(OBJS) $(OBJS2)
	
fclean: clean
	-rm -rf $(NAME) $(NAME2)

re:		fclean all

.PHONY: all clean fclean re