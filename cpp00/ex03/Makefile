# create makefile for the project
# This Makefile is used to build the project and manage dependencies	
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = iostream.cpp classes.cpp
OBJS = $(SRCS:.cpp=.o)

NAME = classes
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
# This Makefile is used to build the project and manage dependencies
# It compiles the source files into object files and links them into an executable
# The project uses C++98 standard and includes necessary flags for warnings
# The clean target removes object files and the executable
# The fclean target extends clean to also remove the executable
# The re target combines fclean and all to rebuild the project from scratch
# The .PHONY directive indicates that these targets are not actual files	
