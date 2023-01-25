
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=surcharge

SRCS=test_surcharge.cpp

OBJS=$(SRCS:cpp=o)

CXX=c++

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Wfatal-errors -g

LDFLAGS=-lstdc++ -lm

$(NAME) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

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
