CC = c++ -Wall -Wextra -Werror -std=c++98


src = Account.cpp test.cpp


obj = $(src:.cpp=.o)

NAME = account

all: $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@


$(NAME): $(obj)
	$(CC) -o $(NAME) $(obj)

clean:
	rm -f $(obj) $(NAME)

fclean:
	rm -f $(obj) $(NAME)

re: clean fclean all

.PHONY: all clean fclean re