CC = c++ -Wall -Wextra -Werror -std=c++11

src = phonebook.cpp

obj = $(src:.cpp=.o)

NAME = phonebook

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