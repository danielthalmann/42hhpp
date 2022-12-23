
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=client-server

SRCS=server.cpp client.cpp

OBJS=$(SRCS:cpp=o)

CXX=c++

CXXFLAGS=-Wall -Wextra -Werror -std=c++98

LDFLAGS=-lstdc++ -lm

$(NAME) : client server

client : $(OBJS)
	$(CXX) client.o $(LDFLAGS) -o client

server : $(OBJS)
	$(CXX) server.o $(LDFLAGS) -o server

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

debug : CXXFLAGS += -DDEBUG
debug : re run

run : $(NAME)
	./$(NAME)
