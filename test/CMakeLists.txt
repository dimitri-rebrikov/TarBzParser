add_executable(BzReaderTest BzReaderTest.c)
add_executable(TarParserTest TarParserTest.c)
add_executable(TarBzParserTest TarBzParserTest.c)

target_link_libraries(BzReaderTest TarBzParser)  

target_link_libraries(TarParserTest TarBzParser)

target_link_libraries(TarBzParserTest TarBzParser)
