add_executable(BzReaderTest BzReaderTest.c)
target_link_libraries(BzReaderTest TarBzParser)  
add_test(NAME BzReaderTest COMMAND bash -c "./BzReaderTest ../../test/BzReaderTest1.txt.bz2 BzReaderTest1.txt && diff ./../test/BzReaderTest1.txt BzReaderTest1.txt" )

add_executable(TarParserTest TarParserTest.c)
target_link_libraries(TarParserTest TarBzParser)
add_test(NAME TarParserTest COMMAND bash -c "./TarParserTest ../../test/TarParserTest1.tar TarParserTest1.txt && diff ./../test/TarParserTest1.txt TarParserTest1.txt" )

add_executable(TarBzParserTest TarBzParserTest.c)
target_link_libraries(TarBzParserTest TarBzParser)
add_test(NAME TarBzParserTest COMMAND bash -c "./TarBzParserTest ../../test/TarBzParserTest1.tar.bz2 TarBzParserTest1.txt && diff ./../test/TarParserTest1.txt TarBzParserTest1.txt" )
