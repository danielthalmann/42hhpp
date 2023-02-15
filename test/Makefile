
# https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

SRC_DIR=../src/
INC_DIR = ../include/
LIB_JSON=../lib/json/bin/json.a
INC_JSON=../lib/json/include

NAME=test

SRCS=test$(TEST_NAME).cpp\
	$(SRC_DIR)Binding.cpp\
	$(SRC_DIR)CGI.cpp\
	$(SRC_DIR)ErrorPage.cpp\
	$(SRC_DIR)Header.cpp\
	$(SRC_DIR)HHPP.cpp\
	$(SRC_DIR)Location.cpp\
	$(SRC_DIR)MimeType.cpp\
	$(SRC_DIR)Redirect.cpp\
	$(SRC_DIR)Request.cpp\
	$(SRC_DIR)Response.cpp\
	$(SRC_DIR)ResponseCgi.cpp\
	$(SRC_DIR)ResponseError.cpp\
	$(SRC_DIR)ResponseFile.cpp\
	$(SRC_DIR)ResponseRedirect.cpp\
	$(SRC_DIR)Server.cpp\
	$(SRC_DIR)utility.cpp

OBJS=$(SRCS:cpp=o)

CXX=c++

CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -Wfatal-errors -g -I$(INC_DIR) -I$(INC_JSON)

LDFLAGS=-lstdc++ -lm


$(NAME) : $(OBJS) $(LIB_JSON)
	$(CXX) $(OBJS) $(LDFLAGS) $(LIB_JSON) -o $(NAME)

$(LIB_JSON):
	$(MAKE) -C ../lib/json/

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
