
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=json.a

SRCFILES=Json.cpp JsonObject.cpp JsonString.cpp

SRCS=$(addprefix src/, ${SRCFILES})

OBJS=${SRCS:cpp=o}

CXX=gcc

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude

LDFLAGS=-lstdc++ -lm

BIN_FOLDER=bin/

#$(NAME) : $(OBJS)
#	$(CXX) $(OBJS) $(LDFLAGS) -o $@


${NAME}: ${OBJS}
	ar rsv ${BIN_FOLDER}$@ ${OBJS} 	

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f ${BIN_FOLDER}$(NAME)

re : fclean all

test : $(NAME)
	$(CXX) tests/main.cpp ${BIN_FOLDER}$(NAME) $(CXXFLAGS) $(LDFLAGS) -o bin/test


