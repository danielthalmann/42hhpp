
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=json.a

SRC_FOLDER=src/
BIN_FOLDER=bin/
OBJ_FOLDER=obj/
TEST_FOLDER=tests/

SRCFILES=Json.cpp JsonObject.cpp JsonString.cpp

SRCS=$(addprefix ${SRC_FOLDER}, ${SRCFILES})

#OBJS=${SRCS:cpp=o}
OBJS=$(patsubst %.cpp, ${BUILD}%.o, ${SRCS})

CXX=gcc

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude

LDFLAGS=-lstdc++ -lm


#$(NAME) : $(OBJS)
#	$(CXX) $(OBJS) $(LDFLAGS) -o $@

#$(BUILD)%.o : %.cpp
#	$(CXX) $(CXXFLAGS) $< -o $@

${NAME}: ${OBJS}
	@ar rsv ${BIN_FOLDER}$@ ${OBJS} 	

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f ${BIN_FOLDER}$(NAME)

re : fclean all

test : $(NAME)
	@cd ${TEST_FOLDER} ;	./test.sh


