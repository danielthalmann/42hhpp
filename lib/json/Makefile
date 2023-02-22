
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=json.a

SRC_DIR=src/
BIN_DIR=bin/
OBJ_DIR=obj/
TEST_DIR=tests/

SRCFILES=Json.cpp JsonValue.cpp JsonObject.cpp JsonArray.cpp JsonString.cpp JsonNumber.cpp JsonBoolean.cpp

SRCS=$(addprefix ${SRC_DIR}, ${SRCFILES})

OBJS=$(addprefix ${OBJ_DIR}, ${SRCFILES:cpp=o})

#CXX=gcc
ifeq ($(shell uname), Linux)
	CXX = g++
else ifeq ($(shell c++-12 -dumpversion 2> /dev/null), 12)
	CXX = c++-12
else
	CXX = c++
endif

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Iinclude 

LDFLAGS=-lstdc++ -lm

all: ${BIN_DIR}${NAME}

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

${BIN_DIR}${NAME}: $(OBJ_DIR) ${OBJS}
	@ar rsv $@ ${OBJS} 	

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f ${BIN_DIR}$(NAME)

re : fclean all

test : CXXFLAGS+= -g3 -fsanitize=address
test : all
	@cd ${TEST_DIR} ;	./test.sh


