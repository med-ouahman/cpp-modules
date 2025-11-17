CC = c++ -Wall -Wextra -Werror -std=c++98

SRC = AMateria.cpp Character.cpp Ice.cpp Cure.cpp MateriaSource.cpp main.cpp

OBJ = $(SRC:.cpp=.o)

NAME = abstract

%.o: %.cpp
	$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
