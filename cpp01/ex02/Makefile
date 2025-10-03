CPP = c++ -Wall -Wextra -Werror -std=c++98

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

NAME = brainz

%.o: %.cpp
	$(CPP) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all