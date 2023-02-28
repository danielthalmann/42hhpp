
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

NAME=json.a

SRC_DIR=src/
BIN_DIR=bin/
OBJ_DIR=obj/
TEST_DIR=tests/
INC_DIR=include/

SRCFILES=Json.cpp JsonValue.cpp JsonObject.cpp JsonArray.cpp JsonString.cpp JsonNumber.cpp JsonBoolean.cpp
INCFILES=Json.hpp JsonValue.hpp JsonObject.hpp JsonArray.hpp JsonString.hpp JsonNumber.hpp JsonBoolean.hpp

SRCS=$(addprefix ${SRC_DIR}, ${SRCFILES})
INCS=$(addprefix ${INC_DIR}, ${INCFILES})
OBJS=$(addprefix ${OBJ_DIR}, ${SRCFILES:cpp=o})

#CXX=gcc
ifeq ($(shell uname), Linux)
	CXX = g++
else
	CXX = c++
endif

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -I$(INC_DIR) 

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

# normalize file
lint: 
	clang-format --style=file -i  $(INCS)  $(SRCS) 