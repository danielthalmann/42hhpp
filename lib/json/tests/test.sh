#!/bin/bash

BIN_FOLDER=../bin/
TEST_FOLDER=./
INCLUDE_FOLDER=../include/

build_code () {
    
    printf "[\u1b[32m+\033[0m] compile file "
    gcc ${TEST_FOLDER}main.cpp ${BIN_FOLDER}json.a -Wall -Wextra -Werror -std=c++98 -I${INCLUDE_FOLDER} -lstdc++ -lm -o ${BIN_FOLDER}test 2> /dev/null

    if [ $? -ne 0 ] 
    then
        printf "[\u1b[31mKO\033[0m] file cannot be compiled\n" ;
        return
    fi

    printf "[\u1b[32m+\033[0m] execute test "
    ${BIN_FOLDER}test

    if [ $? -ne 0 ] 
    then
        printf "[\u1b[31mKO\033[0m] error in execution\n" ;
        return
    fi

    printf "[\u1b[32mOK\033[0m]\n" ;
}

build_code


