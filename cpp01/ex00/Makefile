CPP = c++ -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Zombie.cpp newZombie.cpp randomChump.cpp

NAME = zombie

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CPP) -c $< -o $@

$(NAME): $(OBJ)
	$(CPP) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

