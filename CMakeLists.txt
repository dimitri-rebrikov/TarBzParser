cmake_minimum_required(VERSION 3.11...3.23)

project(TarBzParser)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    include(CTest)

endif()

add_subdirectory(src)

add_subdirectory(../bzip2 ./lib/bzip2)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
   AND BUILD_TESTING)
    add_subdirectory(test)
endif()

