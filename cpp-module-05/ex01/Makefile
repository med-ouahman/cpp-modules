CPP = c++ -Wall -Wextra -Werror -std=c++98

NAME = form

SRC = main.cpp Bureaucrat.cpp Form.cpp

OBJS = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CPP) -c $< -o $@

$(NAME): $(OBJS)
	$(CPP) $(OBJS) -o $(NAME)

clean:
	rm -fr $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
