NAME = containers
SRCS = main.cpp 
FLAGS = -Wall -Werror -Wextra
CC = c++ 
CFLAGS = -std=c++98
HEADRS = *.hpp

all :  $(NAME)
$(NAME) : $(SRCS) $(HEADRS)
	@$(CC) $(CFLAGS) $(FLAGS) $(SRCS) -o $(NAME)
clean			:

fclean			: clean
				@/bin/rm -f $(NAME)

re				: fclean all