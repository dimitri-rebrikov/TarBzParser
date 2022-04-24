#include <stdio.h>
#include "TarBzParser/BzReader.h"
#include "TarBzParser/TarParser.h"


size_t readFromFile(void* f, char* buffer, size_t size) {
    return fread(buffer, sizeof(char), size, (FILE*)f);
}

size_t readFromBz(void* f, char* buffer, size_t size) {
    return BzReader_read(f, buffer, size);
}

void printName(void* file, char* name) {
    fprintf((FILE*)file, "Name: %s\n", name);
}

void printData(void* file, char* data, size_t size) {
    fprintf((FILE*)file, "Data: %.*s\n", size, data);
}

int main() {
    char  buf[TAR_BLOCK_SIZE];

    FILE* in  = fopen("../test/TarBzParserTest1.tar.bz2", "r" );
    if (!in ) {
         fprintf(stderr, "cannot open file for read");
         return -1;
    }

    FILE* out = fopen("../test/TarBzParserTest1.txt.tmp", "w+" );
    if(!out) {
        fprintf(stderr, "cannot open file to write");
        return -1;
    }

    BufReader_t fReader;
    BufReader_init(&fReader, &readFromFile, in);

    BzReader_handle_t bzHandle;

    if(BzReader_init(&bzHandle, &fReader)!=0) {
        fprintf(stderr, "error during bzReader_init\n");
        return -1;
    }

    Reader_t bzReader;
    bzReader.parentReader =  &readFromBz;
    bzReader.parentStream = &bzHandle;

    TarParser_callback_t callback;
    callback.dirCallback = &printName;
    callback.fileCallback = &printName;
    callback.dataCallback = &printData;
    callback.context = out;

    TarParser_parse(&bzReader, &callback);

    fclose(in);
    fclose(out);
    
}