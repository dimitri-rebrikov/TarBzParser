cmake_minimum_required(VERSION 3.0.0)

project(TarBzParser)

add_subdirectory(src)

add_subdirectory(../bzip2 ./lib/bzip2)

add_subdirectory(test)
