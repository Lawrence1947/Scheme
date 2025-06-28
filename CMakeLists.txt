cmake_minimum_required(VERSION 3.10)
project(Scheme)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  src/main.cpp
  src/tokenizer.cpp
  src/scheme.cpp
  src/parser.cpp
)

set(HEADERS
  include/tokenizer.h
  include/scheme.h
  include/globals.h
  include/parser.h
  include/objects/object.h
  include/objects/specials/dot.h
  include/objects/specials/quote.h
  include/objects/operations/addition.h
  include/objects/operations/subtraction.h
  include/objects/operations/multiplication.h
  include/objects/operations/division.h
  include/objects/operations/greater.h
  include/objects/operations/less.h
  include/objects/operations/equal.h
  include/objects/types/symbol.h
  include/objects/types/cell.h
  include/objects/types/function.h
  include/objects/types/number.h
  include/objects/types/bool.h
  include/objects/keywords/and.h
  include/objects/keywords/or.h
  include/objects/keywords/not.h
  include/objects/keywords/bool_predicate.h
  include/objects/keywords/define.h
  include/objects/keywords/set.h
  include/objects/keywords/if.h
  include/objects/keywords/lambda.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} 
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format)
endif()
