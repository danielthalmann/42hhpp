#!/bin/bash

BIN_FOLDER=./
TEST_FOLDER=./

TEST_NAMES=('MapStringToArray')

make  TEST_NAME=test fclean > /dev/null
set -e

build_code () {
    
    printf "[\x1b[32m+\x1b[0m] compile file ${TEST_NAME} "
    # DEBUG_FLAG="-g "
    DEBUG_FLAG="-g3 -fsanitize=address "
    make TEST_NAME=${TEST_NAME} > /dev/null
    if [ $? -ne 0 ] 
    then
        printf "[\x1b[31mKO\x1b[0m] file cannot be compiled\n" ;
        return
    fi

    printf "[\x1b[32m+\x1b[0m] execute test "
    ${BIN_FOLDER}test

    if [ $? -ne 0 ] 
    then
        printf "[\x1b[31mKO\x1b[0m] error in execution\n" ;
        return
    fi

    printf "[\x1b[32mOK\x1b[0m]\n" ;
}

for TEST_NAME in "${TEST_NAMES[@]}"
do
   build_code
done

rm -f *.o 

