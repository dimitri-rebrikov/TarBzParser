cmake_minimum_required(VERSION 3.0.0)

project(TarParser)

add_library(BufReader STATIC
    src/BufReader.c
    src/BufReader.h
)

add_library(BzReader STATIC
    src/BzReader.h
    src/BzReader.c
)

add_library(TarParser STATIC
    src/TarParser.h
    src/TarParser.c
)

add_executable(BzReaderTest src/BzReaderTest.c)
add_executable(TarParserTest src/TarParserTest.c)
add_executable(TarBzParserTest src/TarBzParserTest.c)

add_subdirectory(../bzip2 ./lib/bzip2)

target_link_libraries(BzReader bzip2 BufReader)
target_link_libraries(BzReaderTest BzReader)  

target_link_libraries(TarParser BufReader)
target_link_libraries(TarParserTest TarParser)

target_link_libraries(TarBzParserTest TarParser BzReader)
