file(GLOB HEADER_LIST ../include/TarBzParser/*.h)

add_library(TarBzParser STATIC
    ${HEADER_LIST}
    BufReader.c
    BzReader.c
    TarParser.c
    TarBzParser.c
)

target_include_directories(TarBzParser PUBLIC ../include)
target_link_libraries(TarBzParser bzip2)

