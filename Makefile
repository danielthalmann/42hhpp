ifeq ($(shell uname), Linux)
	CC = g++
else ifeq ($(shell c++-12 -dumpversion), 12)
	CC = c++
else
	CC = c++
endif

RM = rm -rf
CPPFLAGS = -Werror -Wall -Wextra -Wfatal-errors
CPPFLAGS += -std=c++98 -pedantic
CPPFLAGS += -g3 -fsanitize=address

SRC_DIR = src/
_SRC =	main.cpp\
		AResponse.cpp\
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
		ResponseFile.cpp\
		ResponseRedirect.cpp\
		Server.cpp\
		utility.cpp

SRC = $(addprefix $(SRC_DIR), $(_SRC))

INC_DIR = include/
HEADER=	AResponse.hpp\
		Binding.hpp\
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
		ResponseFile.hpp\
		ResponseRedirect.hpp\
		Server.hpp\
		utility.hpp

INC = $(addprefix $(INC_DIR), $(HEADER))

NAME = hhpp

OBJ_DIR = obj/
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ))

.PHONY: all clean fclean re run leak json

all: $(NAME)

#TODO a corriger et ajouter la dependance
json:
	$(MAKE) -C lib/json/

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) ./Makefile | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

run:
	./$(NAME)

leak: CPPFLAGS = -Werror -Wall -Wextra -std=c++98 -pedantic -g3
leak: re
	leaks -atExit -- ./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM

re: fclean all