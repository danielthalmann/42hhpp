ifeq ($(shell uname), Linux)
	CC = g++
else ifeq ($(shell c++-12 -dumpversion), 12)
	CC = g++-12
else
	CC = c++
endif

RM = rm -rf
CFLAGS = -Werror -Wall -Wextra -Wfatal-errors
CFLAGS += -std=c++98 -pedantic
CFLAGS += -g3 -fsanitize=address

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
		Server.cpp

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
		Server.hpp

INC = $(addprefix $(INC_DIR), $(HEADER))

NAME = hhpp

OBJ_DIR = obj/
_OBJ = $(_SRC:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ))

.PHONY: all clean fclean re run leak

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(INC) ./Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

run:
	./$(NAME)

leak: CFLAGS = -Werror -Wall -Wextra -std=c++98 -pedantic -g3
leak: re
	leaks -atExit -- ./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME).dSYM

re: fclean all