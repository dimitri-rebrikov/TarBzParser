#include <stdio.h>
#include "TarBzParser/BzReader.h"

/** 
 * abstract reader function 
 */
size_t readFromFile(void* f, char* buffer, size_t size) {
    return fread(buffer, sizeof(char), size, (FILE*)f);
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "provide 2 parameters: <BzFilePathToReadFrom> <OutputFilePathToExtractInto");
        return -1;
    }

    char* bzFilePath = argv[1];
    char* outFilePath = argv[2];

    bz_stream bStream;
    char  buf[BUF_READER_BUFFER_SIZE];

    FILE* in  = fopen (bzFilePath, "r" );
    if (!in ) {
         fprintf(stderr, "Cannot open file \"%s\" to read from.", bzFilePath);
         return -1;
    }

    FILE* out = fopen(outFilePath, "w+" );
    if(!out) {
        fprintf(stderr, "Cannot open file \"%s\" to write to.", outFilePath);
        return -1;
    }

    BufReader_t reader;
    BufReader_init(&reader, &readFromFile, in);

    BzReader_handle_t bzHandle;

    if(BzReader_init(&bzHandle, &reader)!=0) {
        fprintf(stderr, "error during bzReader_init\n");
        return -1;
    }

    int read;
    do {
        read = BzReader_read(&bzHandle, buf, sizeof(buf));
        if(read > 0) {
            printf("Decompressed %d bytes \n", read);
            fwrite(buf, sizeof(char), read, out);
        }
    } while (read == sizeof(buf));

    BzReader_close(&bzHandle);

    fclose(in);
    fclose(out);
    
}