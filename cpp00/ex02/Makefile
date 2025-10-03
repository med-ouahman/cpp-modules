CC = c++ -Wall -Wextra -Werror -std=c++98

SRC = Account.cpp tests.cpp

OBJ = $(SRC:.cpp=.o)

NAME = account

all: $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(NAME)

fclean:
	rm -f $(OBJ) $(NAME)

re: clean fclean all

.PHONY: all clean fclean re