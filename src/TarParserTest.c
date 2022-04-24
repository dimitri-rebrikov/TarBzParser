#include <stdio.h>
#include "TarParser.h"

/** 
 * abstract reader function 
 */
size_t readFromFile(void* f, char* buffer, size_t size) {
    return fread(buffer, sizeof(char), size, (FILE*)f);
}

void printName(void* file, char* name) {
    fprintf((FILE*)file, "Name: %s\n", name);
}

void printData(void* file, char* data, size_t size) {
    fprintf((FILE*)file, "Data: %.*s\n", size, data);
}

int main() {
    char  buf[TAR_BLOCK_SIZE];

    FILE* in  = fopen("../test/TarParserTest1.tar", "r" );
    if (!in ) {
         fprintf(stderr, "cannot open file for read");
         return -1;
    }

    FILE* out = fopen("../test/TarParserTest1.txt.tmp", "w+" );
    if(!out) {
        fprintf(stderr, "cannot open file to write");
        return -1;
    }

    Reader_t reader;
    reader.parentReader =  &readFromFile;
    reader.parentStream = in;

    TarParser_callback_t callback;
    callback.dirCallback = &printName;
    callback.fileCallback = &printName;
    callback.dataCallback = &printData;
    callback.context = out;

    TarParser_parse(&reader, &callback);

    fclose(in);
    fclose(out);
    
}