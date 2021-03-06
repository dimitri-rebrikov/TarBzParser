#include <stdio.h>
#include "TarBzParser/TarBzParser.h"


size_t readFromFile(void* f, char* buffer, size_t size) {
    return fread(buffer, sizeof(char), size, (FILE*)f);
}

void printName(void* file, char* name) {
    fprintf((FILE*)file, "Name: %s\n", name);
}

void printData(void* file, char* data, size_t size) {
    fprintf((FILE*)file, "Data: %.*s\n", size, data);
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "provide 2 parameters: <TarBzFilePathToReadFrom> <OutputFilePathToParseInto");
        return -1;
    }

    char* tarFilePath = argv[1];
    char* outFilePath = argv[2];

    char  buf[TAR_BLOCK_SIZE];

    FILE* in  = fopen(tarFilePath, "r" );
    if (!in ) {
         fprintf(stderr, "cannot open file \"%s\" for read from ", tarFilePath);
         return -1;
    }

    FILE* out = fopen(outFilePath, "w+" );
    if(!out) {
          fprintf(stderr, "Cannot open file \"%s\" to write to.", outFilePath);
        return -1;
    }

    Reader_t fReader;
    fReader.parentReader = &readFromFile;
    fReader.parentStream = in;
   
    TarParser_callback_t callback;
    callback.dirCallback = &printName;
    callback.fileCallback = &printName;
    callback.dataCallback = &printData;
    callback.context = out;

    if(TarBzParser_parse(&fReader, &callback)!=0) {
        fprintf(stderr, "error during TarBzParser_parse\n");
        return -1;
    }

    fclose(in);
    fclose(out);
    
}