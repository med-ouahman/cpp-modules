CC = g++ -Wall -Wextra -Werror -std=c++98


src = main.cpp

obj = $(src:.cpp=.o)

NAME = relpace

%.o: %.cpp
	$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(obj)
	$(CC) -o $(NAME) $(obj)

clean:
	rm -f $(obj) $(NAME)

fclean:
	rm -f $(obj) $(NAME)

re: clean fclean all

.PHONY: all clean fclean re
