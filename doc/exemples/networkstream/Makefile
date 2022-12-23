
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=stream

SRCS=main.cpp NetworkStream.cpp NetworkBuffer.cpp

OBJS=$(SRCS:cpp=o)

CXX=c++

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Wfatal-errors

LDFLAGS=-lstdc++ -lm

$(NAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o client

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
