
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=json.a

SRCFILES=json.cpp

SRCS=$(addprefix src/, ${SRCFILES})

OBJS=${SRCS:cpp=o}

CXX=gcc

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude

LDFLAGS=-lstdc++ -lm

#$(NAME) : $(OBJS)
#	$(CXX) $(OBJS) $(LDFLAGS) -o $@

${NAME}: ${OBJS}
	ar rsv $@ ${OBJS} 	

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

run : $(NAME)
	./$(NAME)
