CC = c++ -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Dog.cpp Animal.cpp Cat.cpp Brain.cpp

OBJS = $(SRC:.cpp=.o)

NAME = poly

%.o: %.cpp
	$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re