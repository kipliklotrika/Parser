cmake_minimum_required(VERSION 3.5)

project(Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a list with all .cpp source files
set( project_sources
   main.cpp
   parser.cpp
   interpreter.cpp
   lexer.cpp
   astnode.cpp
   number.cpp
   binaryoperator.cpp
)

add_executable(Parser ${project_sources})
