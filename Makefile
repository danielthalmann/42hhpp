ifeq ($(shell uname), Linux)
	CXX = g++
else ifeq ($(shell c++-12 -dumpversion 2> /dev/null), 12)
	CXX = c++-12
else
	CXX = c++
endif

RM = rm -rf
CXXFLAGS = -Werror -Wall -Wextra -Wfatal-errors
CXXFLAGS += -std=c++98 -pedantic
CXXFLAGS += -I$(INC_DIR) -I$(INCLUDE_JSON)
CXXFLAGS += -g
#CXXFLAGS += -g3 -fsanitize=address

SRC_DIR = src/

_SRC =	main.cpp\
		Server.cpp\
		Binding.cpp\
		CGI.cpp\
		ErrorPage.cpp\
		Header.cpp\
		HHPP.cpp\
		Location.cpp\
		MimeType.cpp\
		Redirect.cpp\
		Request.cpp\
		Response.cpp\
		ResponseCgi.cpp\
		ResponseError.cpp\
		ResponseFile.cpp\
		ResponseRedirect.cpp\
		utility.cpp

SRC = $(addprefix $(SRC_DIR), $(_SRC))

INC_DIR = include/
HEADER=	Binding.hpp\
		CGI.hpp\
		ErrorPage.hpp\
		Header.hpp\
		HHPP.hpp\
		IBinding.hpp\
		IServer.hpp\
		Location.hpp\
		MimeType.hpp\
		Redirect.hpp\
		Request.hpp\
		Response.hpp\
		ResponseCgi.cpp\
		ResponseError.cpp\
		ResponseFile.hpp\
		ResponseRedirect.hpp\
		Server.hpp\
		utility.hpp

INC = $(addprefix $(INC_DIR), $(HEADER))

NAME = hhpp

OBJ_DIR = obj/
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ))

LIB_JSON=lib/json/bin/json.a
JSON_DIR=lib/json/
INCLUDE_JSON=lib/json/include

.PHONY: all clean fclean re run leak json

all: $(NAME)

#TODO a corriger et ajouter la dependance
$(LIB_JSON):
	$(MAKE) -C $(JSON_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_JSON)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIB_JSON) -o $(NAME)

run:
	./$(NAME)

leak: CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -pedantic -g3
leak: re
	leaks -atExit -- ./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM
	make -C $(JSON_DIR) fclean

re: fclean all

# normalize file
lint: 
	clang-format --style=file -i  $(INC)  $(SRC) 