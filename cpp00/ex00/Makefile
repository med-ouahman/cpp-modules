compiler = g++ -Wall -Wextra -Werror

src = megaphone.c

NAME = megaphone

obj = megaphone.o

%.o: %c
	$(compiler) -c $(src) -o $(obj)

all: $(NAME)

$(NAME): $(obj)
	$(compiler) $(obj) -o $(NAME)

