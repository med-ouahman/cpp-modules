CPP = c++ -Wall -Wextra -Werror

src = megaphone.cpp

NAME = megaphone

OBJ = $(src:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CPP) -c $< -o $@

$(NAME): $(OBJ)
	$(CPP) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re