
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=json.a

SRC_FOLDER=src/
BIN_FOLDER=bin/
OBJ_FOLDER=obj/
TEST_FOLDER=tests/

SRCFILES=Json.cpp JsonValue.cpp JsonObject.cpp JsonArray.cpp JsonString.cpp JsonNumber.cpp JsonBoolean.cpp

SRCS=$(addprefix ${SRC_FOLDER}, ${SRCFILES})

#OBJS=${SRCS:cpp=o}
OBJS=$(patsubst %.cpp, ${BUILD}%.o, ${SRCS})

CXX=gcc

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude 

LDFLAGS=-lstdc++ -lm

all: ${BIN_FOLDER}${NAME}

#$(NAME) : $(OBJS)
#	$(CXX) $(OBJS) $(LDFLAGS) -o $@

#$(BUILD)%.o : %.cpp
#	$(CXX) $(CXXFLAGS) $< -o $@

${BIN_FOLDER}${NAME}: ${OBJS}
	@ar rsv $@ ${OBJS} 	

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f ${BIN_FOLDER}$(NAME)

re : fclean all

test : CXXFLAGS+= -g3 -fsanitize=address
test : all
	@cd ${TEST_FOLDER} ;	./test.sh


